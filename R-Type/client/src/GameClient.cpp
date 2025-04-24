/*
** EPITECH PROJECT, 2024
** GameClient.cpp
** File description:
** R-Type
*/

#include <iostream>
#include <string>
#include "Renderer/SFMLRenderer.hpp"
#include "GameClient.hpp"

static std::string trimNulls(const std::string& str)
{
    size_t end = str.find_last_not_of('\0');
    return str.substr(0, end + 1); 
}


GameClient::GameClient(const std::string& ip_adress, int port) : _audio(nullptr), _renderer(nullptr),
                        _networkManager(std::make_shared<NetworkManager>(ip_adress, port)),
                        _playerID(-1),
                        _score(0),
                        _is_ready(false),
                        _previousState(GameStateRendering::QUIT_SERVER)
{
    try {
        _loaderRenderer.load("./lib/libSFMLRenderer.so");
        _renderer = std::shared_ptr<IRenderer>(_loaderRenderer.getInstance(ENTRYPOINT));
        _loaderAudio.load("./lib/libSFMLAudio.so");
        _audio = std::shared_ptr<IAudio>(_loaderAudio.getInstance(ENTRYPOINT));
        Logger::getInstance()->info("Renderer loaded and initialized.");
    } catch (const std::exception& e) {
        Logger::getInstance()->error("Failed to initialize renderer: {}", e.what());
        throw;
    }
    Logger::getInstance()->info("GameClient initialized.");

}

GameClient::~GameClient() 
{
    destroyObjects();
    try {
        _loaderRenderer.unload();
        _loaderAudio.unload();
        Logger::getInstance()->info("Renderer library & Audio library unloaded.");
    } catch (const std::exception& e) {
        Logger::getInstance()->error("Error unloading renderer library: {}", e.what());
    }
    Logger::getInstance()->info("GameClient destroyed.");
}

void GameClient::connectServer()
{
    _networkManager->connectToServer("John Doe");
    while (_networkManager->getClientId() == -1) {
        continue;
    }
    setPlayerID(_networkManager->getClientId());
    _renderer->setCrtPlayerID(_networkManager->getClientId());
    _renderer->setIsShootingGame(_networkManager->getIsShootingGame());
    Logger::getInstance()->info("Connected to server. Assigned PlayerID: {}", _playerID);
}

void GameClient::loadObjects()
{
	_audio->addSound(GameEvent::COLLISION, "./assets/sounds/collision.wav");
    _audio->addSound(GameEvent::SHOOT, "./assets/sounds/pew-pew.wav");
    _audio->addSound(GameEvent::MENU_EVENT, "./assets/sounds/default-menu.wav");
    _audio->addSound(GameEvent::GAME_EVENT, "./assets/sounds/default-game.wav");
    _audio->addSound(GameEvent::WIN_EVENT, "./assets/sounds/win.wav");
    _audio->addSound(GameEvent::DEAD_EVENT, "./assets/sounds/dead.wav");
    Logger::getInstance()->info("Audio assets loaded.");
    auto entities = _networkManager->getEntities();
    _renderer->initRenderer(entities);
    Logger::getInstance()->info("Load objects from server to assetManager", _playerID);
}

int GameClient::runGameLoop()
{
    Logger::getInstance()->info("Starting game loop.");
    auto entities = _networkManager->getEntities();
    while (_renderer->getCurrentState() != GameStateRendering::QUIT_SERVER) {
        entities = _networkManager->getEntities();
        if (entities.empty()) {
            Logger::getInstance()->error("Entities map is empty.");
            continue;
        }

        if (entities.find(_playerID) == entities.end()) {
            Logger::getInstance()->error("runGameLoop: PlayerID {} not found in entities map.", _playerID);
            return 1;
        }
        _networkManager->processAsyncTasks();
        for (auto [id, entity]: entities) {
            Logger::getInstance()->info("ENTITY ID {}, TYPE {}, X {}, Y {}, velX {}, velY {}, ScX {}, ScY {}", 
            entity->getId(), static_cast<int>(entity->getType()), 
            entity->getX(), entity->getY(), 
            entity->getVel_x(), entity->getVel_y(), 
            entity->getSc_x(), entity->getSc_y());
        }
        handleBackgroundMusic();
        handleSoundOfEvents();
        if (_renderer->getCurrentState() == GameStateRendering::ACCEPT && _is_ready == false) {
            _networkManager->sendReadyPacket();
            _is_ready = true;
        }
        if (_renderer->getCurrentState() == GameStateRendering::QUIT_ROOM) {
            _networkManager->sendQuitPacket();
            std::cout << "SEND QUIT ROOM " << std::endl;
        }
        if (_renderer->getCurrentState() != GameStateRendering::GAME) {
            _renderer->handleInput(entities[_playerID], entities);
            _renderer->clearScreen();
            _renderer->render(entities);
            continue;
        }
        if (_renderer->getCurrentState() == GameStateRendering::GAME) {
            updateEntities(entities);
            _renderer->handleInput(entities[_playerID], entities);
            sendPlayerUpdates(entities[_playerID]);
            if (_networkManager->getIsShootingGame() == true)
                handleCollisions(entities);
            _renderer->clearScreen();
            _renderer->render(entities);
        }
    }
    _networkManager->disconnectFromServer();
    Logger::getInstance()->info("Exiting game loop.");
    return 0;
}

void GameClient:: handleBackgroundMusic()
{
    if (_renderer->getCurrentState() != _previousState) {
        if (_renderer->getCurrentState() == GameStateRendering::MENU ||
        _renderer->getCurrentState() == GameStateRendering::QUIT_ROOM) {
            _audio->stopBackgroundSound();
            _audio->playBackgroundSound(GameEvent::MENU_EVENT, true);
        } else if (_renderer->getCurrentState() == GameStateRendering::GAME) {
            _audio->stopBackgroundSound();
            _audio->playBackgroundSound(GameEvent::GAME_EVENT, true);
        }
        _previousState = _renderer->getCurrentState();
    }
}

void GameClient::handleSoundOfEvents()
{
    GameEvent event = _renderer->getCurrentEvent();
    if (event == GameEvent::MENU_EVENT || event == GameEvent::GAME_EVENT
    || event == GameEvent::PLAYER_LEFT || event == GameEvent::PLAYER_UP
    || event == GameEvent::PLAYER_RIGHT || event == GameEvent:: PLAYER_DOWN
    || event == GameEvent::DEFAULT)
        return;
    _audio->playSound(event);
}

void GameClient::updateEntities(std::unordered_map<int, std::shared_ptr<Entity>>& entities)
{
    for (auto& [id, entity] : entities) {
        if (entity->getType() ==  EntityType::PLAYER || entity->getType() ==  EntityType::ME) {

            if (entity->getId() == _networkManager->getClientId() && _networkManager->getIsShootingGame() == false)  {
                entity->setY(entity->getY() + 5);
                if (entity->getY() < 0) entity->setY(WINDOW_HEIGHT);
                if (entity->getY() > WINDOW_HEIGHT) entity->setY(0);
            }
            if (_networkManager->getIsShootingGame() == true ) {
                auto& bullets = entity->getBullets();
                for (auto it = bullets.begin(); it != bullets.end();) {
                    it->move();
                    if (it->isOutOfBounds(WINDOW_WIDTH, WINDOW_HEIGHT)) {
                        it = bullets.erase(it);
                    } else {
                        ++it;
                    }
                }
            }

        }
    }
}

void GameClient::handleCollisions(std::unordered_map<int, std::shared_ptr<Entity>>& entities)
{
    try {
        Logger::getInstance()->info("handleCollisions: Checking if PlayerID {} exists in entities map.", _playerID);

        if (entities.find(_playerID) == entities.end()) {
            Logger::getInstance()->error("handleCollisions: PlayerID {} not found in entities map.", _playerID);
            return; 
        }

        auto& bullets = entities.at(_playerID)->getBullets();

        std::vector<int> enemiesToRemove;
        const AssetManager assetManager = _renderer->getAssetManager();

        for (auto it = bullets.begin(); it != bullets.end();) {
            bool bulletRemoved = false;

            for (auto& [id, entity] : entities) {
                if (entity->getType() == EntityType::ENEMY) {
                    try {
                        auto contentKey = trimNulls(entity->getContent());
                        Logger::getInstance()->info("handleCollisions: Checking collision for bullet at ({}, {}) with entity ID {}.", 
                                                     it->getX(), it->getY(), id);

                        Logger::getInstance()->info("handleCollisions: Accessing enemy textures for key '{}'.", contentKey);

                        auto& enemyTexture = assetManager.getEnemyTextures().at(contentKey);

                        if ((it->getX() >= entity->getX() && it->getX() <= entity->getX() + enemyTexture.getRecX()) &&
                            (it->getY() >= entity->getY() && it->getY() <= entity->getY() + enemyTexture.getRecY())) {
                            Logger::getInstance()->info("handleCollisions: COLLISION detected with enemy ID {}.", id);

                            enemiesToRemove.push_back(id);
                            it = bullets.erase(it);
                            bulletRemoved = true;
                            break;
                        }
                    } catch (const std::out_of_range& e) {
                        Logger::getInstance()->error(
                            "handleCollisions: Error accessing enemy textures for key '{}'. Exception: {}",
                            trimNulls(entity->getContent()), e.what()
                        );
                        throw; 
                    }
                }
            }

            if (!bulletRemoved) {
                ++it;
            }
        }
        for (int id : enemiesToRemove) {
            Logger::getInstance()->info("handleCollisions: Sending COLLISION packets for enemy ID {}.", id);
            _renderer->setCurrentEvent(GameEvent::COLLISION);
            _renderer->setCurrentSubtitleEvent(SubtitleEvent::COLLISION);
            _networkManager->sendCollisionPacket(_playerID, id);
        }
    } catch (const std::out_of_range& e) {
        Logger::getInstance()->error("handleCollisions: Out-of-range exception: {}", e.what());
        throw;
    } catch (const std::exception& e) {
        Logger::getInstance()->error("handleCollisions: Unexpected exception: {}", e.what());
        throw;
    }
}


// void GameClient::handleCollisions(std::unordered_map<int, std::shared_ptr<Entity>>& entities)
// {
//     if (entities.find(_playerID) != entities.end()) {
//         auto& bullets = entities.at(_playerID)->getBullets();
//         std::vector<int> enemiesToRemove;
//         const AssetManager assetManager = _renderer->getAssetManager();

//         for (auto it = bullets.begin(); it != bullets.end();) {
//             bool bulletRemoved = false;
//             for (auto& [id, entity] : entities) {
//                 if (entity->getType() == EntityType::ENEMY) {
//                     if ((it->getX() >= entity->getX() && it->getX() <= entity->getX() + assetManager.getEnemyTextures().at(trimNulls(entity->getContent())).getRecX()) &&
//                         (it->getY() >= entity->getY() && it->getY() <= entity->getY() + assetManager.getEnemyTextures().at(trimNulls(entity->getContent())).getRecY())) {
//                         Logger::getInstance()->info("COLLISION COLLISION");
//                         enemiesToRemove.push_back(id);
//                         it = bullets.erase(it);
//                         bulletRemoved = true;
//                         break;
//                     }
//                 }
//             }

//             if (!bulletRemoved) {
//                 ++it;
//             }
//         }

//         for (int id : enemiesToRemove) {
//             Logger::getInstance()->info("Sending COLLISION packets enemy {}", id);
//             _renderer->setCurrentEvent(GameEvent::COLLISION);
//             _renderer->setCurrentSubtitleEvent(SubtitleEvent::COLLISION);
//             _networkManager->sendCollisionPacket(_playerID, id);
//         }
//     }
// }


void GameClient::sendPlayerUpdates(std::shared_ptr<Entity> player)
{
    _networkManager->sendInputPacket(
        player->getId(), 
        player->getX(), 
        player->getY(), 
        player->getIsShooting()
    );
}

void GameClient::destroyObjects()
{
    Logger::getInstance()->info("Destroying all entities.");
    _renderer.reset();
    _networkManager.reset();
    Logger::getInstance()->info("Resources cleared.");
}

void GameClient::setPlayerID(int id)
{
    _playerID = id;
    Logger::getInstance()->info("PlayerID set to {}", id);
}