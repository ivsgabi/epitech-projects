/*
** EPITECH PROJECT, 2025
** MenusRendering.cpp
** File description:
** MenusRendering
*/

#include "Renderer/MenusRendering.hpp"

MenusRendering::MenusRendering(AssetManager& assetManager, std::stack<GameStateRendering>& stateStack)
    : _assetManager(assetManager), _stateStack(stateStack)
{
    _blurOverlay.setSize(sf::Vector2f(1920, 1080));
    _blurOverlay.setFillColor(sf::Color(0, 0, 0, 150));

    _shortcutTexture.loadFromFile("./assets/decors/shortcuts.png");
    _shortcutSprite.setTexture(_shortcutTexture);
    sf::FloatRect bounds = _shortcutSprite.getLocalBounds();
    _shortcutSprite.setOrigin(bounds.width / 2.0f, bounds.height / 2.0f);
    _shortcutSprite.setPosition(1920 / 2.0f, 1080 / 2.0f);
}

void MenusRendering::initialize()
{
    std::vector<std::string> opt = DEFAULT_MENU;
    _menu1System = std::make_shared<MenuSystem>(
        _assetManager.getMenuTexture().at("bg-menu"),
        _assetManager.getMenuTexture().at("logo"),   
        _assetManager.getFont(),
        opt,
        false
    );
   
    _menu2System = std::make_shared<MenuSystem>(
        _assetManager.getMenuTexture().at("bg-menu"),
        _assetManager.getMenuTexture().at("logo"),
        _assetManager.getFont(),
        _assetManager.getTextOptions(),
        true
    );

    _levelsSelection = std::make_shared<AssetPlayerSelection>(
        _assetManager.getFont(),
        _assetManager.getMenuTexture().at("bg-menu"),
        _assetManager.getLevelTextures()
    );

    _assetsSelection = std::make_shared<AssetPlayerSelection>(
        _assetManager.getFont(),
        _assetManager.getMenuTexture().at("bg-menu"),
        _assetManager.getPlayerTextures()
    );

    _configSummary = std::make_shared<ConfigSummary>(
        _assetManager.getFont(),
        _assetManager.getMenuTexture().at("bg-menu"),
        _assetManager.getPlayerTextures()
    );
}

void MenusRendering::render(GameStateRendering crtState, sf::RenderWindow& window, const std::unordered_map<int, std::shared_ptr<Entity>>& entities)
{
    switch (crtState) {
        case GameStateRendering::QUIT_ROOM:
        case GameStateRendering::MENU:
            renderMenu(window);
            break;
        case GameStateRendering::MENU_OPT:
            renderMenuOpt(window);
            break;
        case GameStateRendering::HELP:
            renderHelp(window);
            break;
        case GameStateRendering::ASSET_PLAYER:
            renderAssetPlayer(window);
            break;
        case GameStateRendering::LEVELS:
            renderLevels(window);
            break;
        case GameStateRendering::ACCEPT:
            renderAccept(window, entities);
            break;
        case GameStateRendering::CONFIG_SUMMARY:
            renderConfigSummary(window, entities);
            break;
        default:
            break;
    }
}

void MenusRendering::handleInput(GameStateRendering crtState, const sf::Event& event, std::shared_ptr<Entity> crt_player)
{
    switch (crtState) {
        case GameStateRendering::QUIT_ROOM:
        case GameStateRendering::MENU:
            handleMenuInput(event);
            break;
        case GameStateRendering::MENU_OPT:
            handleMenuOptInput(event, crt_player);
            break;
        case GameStateRendering::HELP:
            handleHelpInput(event);
            break;
        case GameStateRendering::ASSET_PLAYER:
            handleAssetPlayerInput(event);
            break;
        case GameStateRendering::LEVELS:
            handleLevelsInput(event);
            break;
        case GameStateRendering::CONFIG_SUMMARY:
            handleConfigSummaryInput(event);
            break;
        default:
            break;
    }
}

void MenusRendering::renderMenu(sf::RenderWindow& window)
{
    _menu1System->render(window);
}

void MenusRendering::renderMenuOpt(sf::RenderWindow& window)
{
    _menu2System->render(window);
}

void MenusRendering::renderHelp(sf::RenderWindow& window)
{
    window.draw(_blurOverlay);
    window.draw(_shortcutSprite);
}

void MenusRendering::renderAssetPlayer(sf::RenderWindow& window)
{
    _assetsSelection->render(window);
}

void MenusRendering::renderLevels(sf::RenderWindow& window)
{
    _levelsSelection->render(window);
}

void MenusRendering:: renderAccept(sf::RenderWindow& window, const std::unordered_map<int, std::shared_ptr<Entity>>& entities)
{
    _configSummary->render(window, entities, 1);
}

void MenusRendering::renderConfigSummary(sf::RenderWindow& window, const std::unordered_map<int, std::shared_ptr<Entity>>& entities)
{
    _configSummary->render(window, entities, 0);
}

void MenusRendering::handleMenuInput(const sf::Event& event)
{
    _menu1System->handleInput(event, _stateStack);
}

static std::string trimNulls(const std::string& str)
{
    size_t end = str.find_last_not_of('\0');
    return str.substr(0, end + 1); 
}

void MenusRendering::handleMenuOptInput(const sf::Event& event, std::shared_ptr<Entity> crt_player)
{
    // find CTR_PLAYER GET HIS PATH asset
    _menu2System->handleInput(event, _stateStack);
    if (_stateStack.top() == GameStateRendering::CONFIG_SUMMARY) {
        _configSummary->setConfig(trimNulls(crt_player->getContent()));
    }
}

void MenusRendering::handleHelpInput(const sf::Event& event)
{
    if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape) {
        _stateStack.pop();
    }
}

void MenusRendering::handleAssetPlayerInput(const sf::Event& event)
{
    _assetsSelection->handleInput(event);
    if (_assetsSelection->getConfirmed()) {
        _stateStack.pop();
        _assetsSelection->resetConfirmed();
    }
}

void MenusRendering::handleLevelsInput(const sf::Event& event)
{
    _levelsSelection->handleInput(event);
    if (_levelsSelection->getConfirmed()) {
        _stateStack.pop();
        _levelsSelection->resetConfirmed();
    }
}

void MenusRendering::handleConfigSummaryInput(const sf::Event& event)
{
    bool confirmed = false, back = false;
    _configSummary->handleInput(event, confirmed, back);
    if (confirmed) {
        _stateStack.push(GameStateRendering::ACCEPT);
    } else if (back) {
        _stateStack.pop();
    }
}
