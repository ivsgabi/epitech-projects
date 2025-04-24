/*
** EPITECH PROJECT, 2024
** SFMLRenderer
** File description:
** SFMLRenderer
*/

#include "Renderer/SFMLRenderer.hpp"
#include "../../../networking/include/Logger.hpp"

extern "C"
{
    SFMLRenderer *entry_point()
    {
        return new SFMLRenderer();
    }
}



SFMLRenderer::SFMLRenderer() :
    _stateStack(), _eventStack(), _subtitleStack()
{
    _stateStack.push(GameStateRendering::MENU);
    _eventStack.push(GameEvent::MENU_EVENT);
    _subtitleStack.push(SubtitleEvent::DEFAULT);
}

SFMLRenderer::~SFMLRenderer()
{
    destroyResources();
}


void SFMLRenderer::initRenderer(const std::unordered_map<int, std::shared_ptr<Entity>>& entities)
{
    for (const auto& [id, entity] : entities) {
        Logger::getInstance()->info("Player RECx={}, RECy={}, ScX={}, ScY={}, nbFrame={}", entity->getX(), entity->getY(), entity->getSc_x(), entity->getSc_y(), entity->getVel_x());

    }
    _assetManager.loadAssetsFromEntities(entities);
    
    _menusRenderer = std::make_shared<MenusRendering>(_assetManager, _stateStack);
    _menusRenderer->initialize();

    _gameRenderer = std::make_shared<GameRendering>(_assetManager, _stateStack, _eventStack, _subtitleStack, _isShootingGame);
    _gameRenderer->initialize(entities, _crtplayerID);

    _window.create(sf::VideoMode(1920, 1080), "R-Type", sf::Style::Close);
    _window.setFramerateLimit(60);
}

void SFMLRenderer::destroyResources()
{

}

void SFMLRenderer::clearScreen()
{
    _window.clear();
}

void SFMLRenderer::render(std::unordered_map<int, std::shared_ptr<Entity>> entities)
{
    switch (getCurrentState()) {
        case GameStateRendering::QUIT_ROOM:
        case GameStateRendering::MENU:
        case GameStateRendering::MENU_OPT:
        case GameStateRendering::HELP:
        case GameStateRendering::ASSET_PLAYER:
        case GameStateRendering::LEVELS:
        case GameStateRendering::ACCEPT:
        case GameStateRendering::CONFIG_SUMMARY:
            _menusRenderer->render(getCurrentState(), _window, entities);
            break;

        case GameStateRendering::GAME:
        case GameStateRendering::WIN:
        case GameStateRendering::DEAD:
            _gameRenderer->render(getCurrentState(), _window, entities, _crtplayerID);
            break;

        default:
            break;
    }
    _window.display();
}

void SFMLRenderer::handleInput(std::shared_ptr<Entity> crt_player, std::unordered_map<int, std::shared_ptr<Entity>> entities)
{
    while (_window.pollEvent(_event)) {
        if (_event.type == sf::Event::Closed) {
            _stateStack = std::stack<GameStateRendering>();
            _window.close();
            return;
        }

        if (_event.type == sf::Event::KeyPressed) {
            if (_event.key.code == sf::Keyboard::S) {
                Logger::getInstance()->info("Sound toggle triggered.");
            }
        }

        switch (getCurrentState()) {
            case GameStateRendering::QUIT_ROOM:
            case GameStateRendering::MENU:
            case GameStateRendering::MENU_OPT:
            case GameStateRendering::HELP:
            case GameStateRendering::ASSET_PLAYER:
            case GameStateRendering::LEVELS:
            case GameStateRendering::CONFIG_SUMMARY:
                _menusRenderer->handleInput(getCurrentState(), _event, crt_player);
                break;
            case GameStateRendering::ACCEPT:{
                if (entities.count(300)) {
                    Logger::getInstance()->info("PUT STATE GAME SFML HANDLE INPUT");
                    _stateStack.push(GameStateRendering::GAME);
                    break;
                }
                break;
            }
            case GameStateRendering::GAME:
            case GameStateRendering::WIN:
            case GameStateRendering::DEAD:
                _gameRenderer->handleInput(getCurrentState(), _event, crt_player, entities);
                break;

            case GameStateRendering::QUIT_SERVER:
                _stateStack = std::stack<GameStateRendering>();
                _window.close();
                break;

            default:
                break;
        }
    }
}

void SFMLRenderer::pushState(GameStateRendering state)
{
    _stateStack.push(state);
}

void SFMLRenderer::popState()
{
    if (!_stateStack.empty()) {
        _stateStack.pop();
    }
}

GameStateRendering SFMLRenderer::getCurrentState() const
{
    return _stateStack.empty() ? GameStateRendering::QUIT_SERVER : _stateStack.top();
}

GameEvent SFMLRenderer::getCurrentEvent()
{
    if (_eventStack.empty())
        return GameEvent::DEFAULT;
    GameEvent event = _eventStack.top();
    _eventStack.pop();
    return event;
}

void SFMLRenderer:: setCurrentEvent(const GameEvent& event)
{
    _eventStack.push(event);
}

void SFMLRenderer:: setCurrentSubtitleEvent(const SubtitleEvent& event)
{
    _subtitleStack.push(event);
}

void SFMLRenderer:: setIsShootingGame(bool isShootingGame)
{
    _isShootingGame = isShootingGame;
}


int SFMLRenderer:: getCrtPlayerID() {
    return _crtplayerID;
}

void SFMLRenderer:: setCrtPlayerID(int crtPlayerID) {
    _crtplayerID = crtPlayerID;
}

const AssetManager& SFMLRenderer:: getAssetManager() {
    return _assetManager;
}
