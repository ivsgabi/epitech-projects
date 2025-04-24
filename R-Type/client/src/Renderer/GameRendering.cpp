/*
** EPITECH PROJECT, 2025
** GameRendering.cpp
** File description:
** GameRendering
*/

#include "Renderer/GameRendering.hpp"
#include <Renderer/BasicComp.hpp>

GameRendering::GameRendering(AssetManager& assetManager, std::stack<GameStateRendering>& stateStack, std::stack<GameEvent>& eventStack, 
std::stack<SubtitleEvent>& subtitleStack, bool& isShootingGame)
    : _assetManager(assetManager), _stateStack(stateStack), _eventStack(eventStack), _subtitleEventStack(subtitleStack), _subtitles(assetManager.getSubtitleFont()), _isShootingGame(isShootingGame)
{
    BasicComp basicComp(_assetManager.getFont());

    _blurOverlay = basicComp.createBlurOverlay({WINDOW_WIDTH, WINDOW_HEIGHT});

    _shortcutTexture.loadFromFile("./assets/decors/shortcuts.png");
    _shortcutSprite = basicComp.createSprite(
        _shortcutTexture, 
        {WINDOW_WIDTH / 2.f, WINDOW_HEIGHT / 2.f}
    );
    _shortcutSprite.setOrigin(_shortcutSprite.getLocalBounds().width / 2.f, 
    _shortcutSprite.getLocalBounds().height / 2.f);

    _popupBox = basicComp.createRectangle(
        {600, 400}, 
        sf::Color(30, 30, 30), 
        sf::Color::White, 
        3.f, 
        {WINDOW_WIDTH / 2.f - 300, WINDOW_HEIGHT / 2.f - 200}
    );

    _popupTitle = basicComp.createCustomText("", 80, sf::Color::White, {0, 0}, sf::Text::Bold);

    _popupScore = basicComp.createCustomText("", 40, sf::Color::White);

    _popupLevel = basicComp.createCustomText("", 40, sf::Color::White);

    _popupInstruction = basicComp.createCustomText(
        "Press ENTER to go back to the menu", 
        40, 
        sf::Color::White
    );

    _scoreText = basicComp.createCustomText(
        "Score", 
        50, 
        sf::Color::Red, 
        {60.0f, 20.f}, 
        sf::Text::Bold
    );

    _levelText = basicComp.createCustomText(
        "Level", 
        50, 
        sf::Color::Yellow, 
        {800.f, 20.f}, 
        sf::Text::Bold
    );

    _infoTexture.loadFromFile("./assets/decors/info.png");
    _infoSprite = basicComp.createSprite(
        _infoTexture, 
        {1800.f, 20.f}
    );
}


static std::string trimNulls(const std::string& str)
{
    size_t end = str.find_last_not_of('\0');
    return str.substr(0, end + 1); 
}

void GameRendering::initialize(const std::unordered_map<int, std::shared_ptr<Entity>>& entities, int crt_playerID)
{
    _backgroundSystem = std::make_shared<BackgroundSystem>(
        _assetManager.getBackgroundTextures(),
        _assetManager.getDecorTextures()
    );
    _playerSystem = std::make_shared<PlayerSystem>(
        _assetManager.getShootTextures(),
        _assetManager.getPlayerTextures(),
        _eventStack,
        _isShootingGame
    );
    _playerSystem->initBulletSprite(DEFAULT_SHOOT_1);
    _playerSystem->initPlayer(trimNulls(entities.at(crt_playerID)->getContent()));
    _enemySystem = std::make_shared<EnemySystem>(
        _assetManager.getEnemyTextures()
    );
    _subtitles.addSubtitle(SubtitleEvent::SHOOT, "pew pew pew");
    _subtitles.addSubtitle(SubtitleEvent::COLLISION, "BOUM BOUM BOUM explosion BOOMMMM");
    _subtitles.addSubtitle(SubtitleEvent::PLAYER_DOWN, "go down");
    _subtitles.addSubtitle(SubtitleEvent::PLAYER_UP, "go up");
    _subtitles.addSubtitle(SubtitleEvent::PLAYER_LEFT, "go left");
    _subtitles.addSubtitle(SubtitleEvent::PLAYER_RIGHT, "go right");
    _subtitles.addSubtitle(SubtitleEvent::WIN_EVENT, "wowowow you win");
    _subtitles.addSubtitle(SubtitleEvent::DEAD_EVENT, "waisted you loose");
    _subtitles.addSubtitle(SubtitleEvent::DEFAULT, "flyinggggg");
}

void GameRendering::render(GameStateRendering crtState, sf::RenderWindow& window, const std::unordered_map<int, std::shared_ptr<Entity>>& entities, int crt_playerId)
{
    switch (crtState) {
        case GameStateRendering::GAME:
            renderGame(window, entities, crt_playerId);
            break;
        case GameStateRendering::WIN:
            renderWin(window, entities, crt_playerId);
            break;
        case GameStateRendering::DEAD:
            renderDead(window, entities, crt_playerId);
            break;
        default:
            break;
    }
}

void GameRendering::handleInput(GameStateRendering crtState, const sf::Event& event, std::shared_ptr<Entity> crtPlayer, std::unordered_map<int, std::shared_ptr<Entity>>& entities)

{
    switch (crtState) {
        case GameStateRendering::WIN:
        case GameStateRendering::DEAD: {
            handleEndGameKeysInput(event);
            break;
        }
        case GameStateRendering::GAME: {
            handleGameKeysInput(event);
            handleEndGame(entities);
            handleUserInput(event, crtPlayer);
            break;
        }
    }
}

void GameRendering:: handleGameKeysInput(const sf::Event& event)
{
    if (event.type == sf::Event::KeyPressed) {
        if (event.key.code == sf::Keyboard::I) {
            _showShortcutPopup = !_showShortcutPopup;
        } else if (event.key.code == sf::Keyboard::Q) {
            _stateStack = std::stack<GameStateRendering>();
            _stateStack.push(GameStateRendering::QUIT_ROOM);
        }
    }

}

void GameRendering:: handleEndGame(const std::unordered_map<int, std::shared_ptr<Entity>>& entities)
{
    if (entities.count(200)) {
        _stateStack.push(GameStateRendering::WIN);
        return;
    }
    if (entities.count(201)) {
        _stateStack.push(GameStateRendering::DEAD);
        return;
    }

}

void GameRendering:: handleUserInput(const sf::Event& event, std::shared_ptr<Entity> crtPlayer)
{
    if (!crtPlayer) {
        Logger::getInstance()->error("crt_player is nullptr!");
        return;
    }
    _playerSystem->handleInput(event, crtPlayer, _subtitleEventStack);
}

void GameRendering:: handleEndGameKeysInput(const sf::Event& event)
{
    if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Enter) {
        _stateStack = std::stack<GameStateRendering>();
        _stateStack.push(GameStateRendering::MENU);
    }
}

void GameRendering:: renderDead(sf::RenderWindow& window, const std::unordered_map<int, std::shared_ptr<Entity>>& entities, int crt_playerId)
{
    renderGame(window, entities, crt_playerId);
    if (entities.count(201)) {
        std::string level = std::to_string(static_cast<int>(entities.at(201)->getX()));
        std::string score = std::to_string(static_cast<int>(entities.at(201)->getY()));
        renderPopup(window, "DEAD", sf::Color::Red, score, level);
    }
}

void GameRendering:: renderWin(sf::RenderWindow& window, const std::unordered_map<int, std::shared_ptr<Entity>>& entities, int crt_playerId)
{
    renderGame(window, entities, crt_playerId);
    if (entities.count(200)) {
        std::string level = std::to_string(static_cast<int>(entities.at(200)->getX()));
        std::string score = std::to_string(static_cast<int>(entities.at(200)->getY()));
        renderPopup(window, "WIN!", sf::Color::Green, score, level);
    }
}

void GameRendering::renderGame(sf::RenderWindow& window, const std::unordered_map<int, std::shared_ptr<Entity>>& entities, int crt_playerId)
{
    // TO BE REMOVED WHEN THE SERVER WILL SEND THE BACKGROUND AND DECOR
    std::string decor = DEFAULT_DECOR_1;
    std::string background;
    for (auto& pair : entities) {
        auto& entity = pair.second;
        if (entity->getType() == EntityType::BACKGROUND) {
            background = trimNulls(entity->getContent());
        }
        if (entity->getType() == EntityType::DECOR) {
            decor = trimNulls(entity->getContent());
        }
    }
    if (!decor.empty() && !background.empty()) {
            _backgroundSystem->init(background, decor);
            _backgroundSystem->update();
            _backgroundSystem->renderBackground(window);
    }
    for (auto& pair : entities) {
        auto& entity = pair.second;
        if (entity->getType() == EntityType::PLAYER || entity->getType() == EntityType::ME) {
            _playerSystem->render(window, entity, crt_playerId);
        }
        if (entity->getType() == EntityType::ENEMY) {
            _enemySystem->render(window, entity);
        }
    }
    _backgroundSystem->renderDecor(window);
    if (entities.count(203)) {
        _scoreText.setString("Score " + trimNulls(entities.at(203)->getContent()));
        window.draw(_scoreText);
    }
    if (entities.count(202)) {
        _levelText.setString("Level " + trimNulls(entities.at(202)->getContent()));
        window.draw(_levelText);
    }
    window.draw(_infoSprite);
    if (_showShortcutPopup) {
        window.draw(_blurOverlay);
        window.draw(_shortcutSprite);
    }
    if (!_subtitleEventStack.empty()) {
        SubtitleEvent currentEvent = _subtitleEventStack.top();
        _subtitles.displaySubtitle(currentEvent, window);
    }

}

void GameRendering::renderPopup(sf::RenderWindow& window, const std::string& title, sf::Color titleColor, const std::string& score, const std::string& level)
{
    const float centerX = WINDOW_WIDTH / 2.0f;
    const float centerY = WINDOW_HEIGHT / 2.0f;
    const float verticalSpacing = 60.0f;

    window.draw(_blurOverlay);
    window.draw(_popupBox);

    _popupTitle.setString(title);
    _popupTitle.setFillColor(titleColor);
    sf::FloatRect titleBounds = _popupTitle.getLocalBounds();
    _popupTitle.setOrigin(titleBounds.width / 2.0f, titleBounds.height / 2.0f);
    _popupTitle.setPosition(centerX, centerY - 2 * verticalSpacing);
    window.draw(_popupTitle);

    _popupScore.setString("Score: " + score);
    sf::FloatRect scoreBounds = _popupScore.getLocalBounds();
    _popupScore.setOrigin(scoreBounds.width / 2.0f, scoreBounds.height / 2.0f);
    _popupScore.setPosition(centerX, centerY - verticalSpacing);
    window.draw(_popupScore);

    _popupLevel.setString("Level: " + level);
    sf::FloatRect levelBounds = _popupLevel.getLocalBounds();
    _popupLevel.setOrigin(levelBounds.width / 2.0f, levelBounds.height / 2.0f);
    _popupLevel.setPosition(centerX, centerY);
    window.draw(_popupLevel);

    _popupInstruction.setString("Press Enter to continue...");
    sf::FloatRect instructionBounds = _popupInstruction.getLocalBounds();
    _popupInstruction.setOrigin(instructionBounds.width / 2.0f, instructionBounds.height / 2.0f);
    _popupInstruction.setPosition(centerX, centerY + verticalSpacing);
    window.draw(_popupInstruction);
}
