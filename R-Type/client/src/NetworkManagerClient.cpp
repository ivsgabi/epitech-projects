/*
** EPITECH PROJECT, 2024
** NetworkManager.cpp
** File description:
** NetworkManager
*/

#include <random>
#include "NetworkManagerClient.hpp"
#include "Renderer/DefaultValues.hpp"

NetworkManager::NetworkManager(const std::string& host, int port) : _clientNetwork(std::make_shared<ClientNetwork>(host, port)) 
{
    Logger::getInstance()->info("Initializing NetworkManager for {}:{}", host, port);
    _clientNetwork->registerSuccessConnectHandler(
        [this](int clientId) {
            handleConnectionSuccess(clientId); }
    );

    _clientNetwork->registerStateUpdateHandler(
        [this](int entityId, int entityType, int posX, int posY, 
               int velX, int velY, int scaleX, int scaleY, bool isFiring) {
            handleStateUpdate(entityId, entityType, posX, posY, velX, velY, scaleX, scaleY, isFiring);
        }
    );

    _clientNetwork->registerSuccessDisconnectHandler(
        [this]() { handleSuccessDisconnect(); }
    );
    _clientNetwork->registerEntityCreateHandler(
        [this](uint32_t entityId, int entityType, const std::string& text, int posX, int posY, 
            int velX, int velY, int scaleX, int scaleY, bool isControllable) {
            handleEntityCreate(entityId, entityType, text, posX, posY, velX, velY, scaleX, scaleY, isControllable);
        }
    );

    _clientNetwork->registerEntityRemoveHandler(
        [this](int entityId) { handleEntityRemove(entityId); }
    );

    _clientNetwork->registerScoreHandler(
        [this] (int entityId, int score) { handleScore(entityId, score); }
    );

    _clientNetwork->registerWonHandler(
        [this] (int entityId, int current_level, int score) { handleWon(entityId, current_level, score); }
    );

    _clientNetwork->registerDeadHandler(
        [this] (int entityId, int current_level, int score) { handleDead(entityId, current_level, score); }
    );

    _clientNetwork->registerLevelHandler(
        [this] (int entityId, int level) { handleLevel(entityId, level); }
    );

    _clientNetwork->registerStartRoomHandler(
        [this] (int entityId) { 
            handleStartRoom(entityId); }
    );

    Logger::getInstance()->info("NetworkManager successfully initialized.");
}

NetworkManager::~NetworkManager()
{
    disconnectFromServer();
}

void NetworkManager::connectToServer(const std::string& name)
{
    try {
        Logger::getInstance()->info("Connecting to server with name: {}", name);
        _clientNetwork->sendConnectPacket(name);
        _clientNetwork->receiveAndDispatchUDP();
        _clientNetwork->run();
    } catch (const std::exception& e) {
        Logger::getInstance()->error("Error connecting to server: {}", e.what());
    }
}

void NetworkManager:: sendInputPacket(int entity_id, int move_x, int move_y, bool firing)
{
    Logger::getInstance()->info("Sending input packet for EntityID: {}", entity_id);
    _clientNetwork->sendInputPacket(entity_id, move_x, move_y, firing);
}

void NetworkManager:: sendCollisionPacket(int entity_id, int enemy_id)
{
    Logger::getInstance()->info("Sending collision packet of EntityID: {} & EnemyId: {}", entity_id, enemy_id);
    _clientNetwork->sendCollisionPacket(entity_id, enemy_id);
}

void NetworkManager:: sendReadyPacket()
{
    Logger::getInstance()->info("ERASE ALL START, WIN, DEAD, SCORE, LEVEL entities to start new game");
    _entities.erase(300);
    _entities.erase(200);
    _entities.erase(201);
    _entities.erase(202);
    _entities.erase(203);
    _clientNetwork->sendClientReadyPacket(_clientId);
    Logger::getInstance()->info("Sending Ready packet");
}

void NetworkManager:: sendQuitPacket()
{
    _clientNetwork->sendClientQuitPacket(_clientId);
    _entities.erase(300);
    _entities.erase(200);
    _entities.erase(201);
    _entities.erase(202);
    _entities.erase(203);
    // server need to erase all the entities players, enemies from the last room
    Logger::getInstance()->info("Sending Quit packet");
}

void NetworkManager::handleConnectionSuccess(int clientId)
{
    Logger::getInstance()->info("Handle connection success");
    
}

void NetworkManager::handleStateUpdate(int entityId, int entityType, int posX, int posY, 
                                       int velX, int velY, int scaleX, int scaleY, bool isFiring)
{
    if (entityId == _clientId)
        return;
    if (_entities.find(entityId) != _entities.end()) {
        auto& entity = _entities[entityId];
        entity->setX(posX);
        entity->setY(posY);
        entity->setVel_x(velX);
        entity->setVel_y(velY);
        entity->setSc_x(scaleX);
        entity->setSc_y(scaleY);
        entity->setIsShooting(isFiring);
        Logger::getInstance()->debug("Updated EntityID {}: Position=({}, {}), Velocity=({}, {})", 
                                     entityId, posX, posY, velX, velY);
        if (isFiring) {
            int bulletX = posX + 20;
            int bulletY = posY;
            int bulletSpeedX = 10;
            int bulletSpeedY = 0;

            entity->addBullet(bulletX, bulletY, bulletSpeedX, bulletSpeedY);
            Logger::getInstance()->info("Added bullet for EntityID {} at Position=({}, {})", entityId, bulletX, bulletY);
        }
    }
}

void NetworkManager::handleSuccessDisconnect()
{
    _entities.clear();
}

void NetworkManager::handleEntityCreate(int entityId, int entityType, const std::string& text, int posX, int posY, 
            int velX, int velY, int scaleX, int scaleY, bool isControllable)
{
    auto entity = std::make_shared<Entity>(
        static_cast<EntityType>(entityType),
        entityId,
        posX,
        posY,
        velX,
        velY,
        scaleX,
        scaleY,
        text
    );
    _entities[entityId] = entity;
    if (entity->getType() == EntityType::ME) 
        _clientId = entity->getId();
    if (entity->getType() == EntityType::IS_SHOOT)
        _isShootingGame = true;
    Logger::getInstance()->info("Created EntityID {}: Type={}, Position=({}, {})", 
                                entityId, entityType, posX, posY);
}

void NetworkManager::handleEntityRemove(int entity_id)
{
    _entities.erase(entity_id);
    Logger::getInstance()->info("===================================================");
    Logger::getInstance()->info("keflzkzfklAKFLKALKFLAKF Removed EntityID {}", entity_id);
    Logger::getInstance()->info("===================================================");
}


void NetworkManager::handleWon(int entity_id, int current_level, int score)
{
    auto entity = std::make_shared<Entity>(
        EntityType::WIN,
        200,
        current_level,
        score,
        -1,
        -1,
        -1,
        -1,
        ""
    );
    _entities[200] = entity;
    Logger::getInstance()->info("Handle WON : current_level {}, score {}", current_level, score);
}

void NetworkManager::handleDead(int entity_id, int current_level, int score)
{
    auto entity = std::make_shared<Entity>(
        EntityType::DEAD,
        201,
        current_level,
        score,
        -1,
        -1,
        -1,
        -1,
        ""
    );
    _entities[201] = entity;
    Logger::getInstance()->info("Handle DEAD : current_level {}, score {}", current_level, score);
}

void NetworkManager::handleLevel(int entity_id, int level)
{
    auto entity = std::make_shared<Entity>(
        EntityType::ASSET_LEVELS,
        202,
        -1,
        -1,
        -1,
        -1,
        -1,
        -1,
        std::to_string(level)
    );
    _entities[202] = entity;
    Logger::getInstance()->info("Handle Level : current_level {}", level);
}

void NetworkManager::handleScore(int entity_id, int score)
{
    auto entity = std::make_shared<Entity>(
        EntityType::SCORE,
        203,
        -1,
        -1,
        -1,
        -1,
        -1,
        -1,
        std::to_string(score)
    );
    _entities[203] = entity;
    Logger::getInstance()->info("Handle score : {}", score);
}

void NetworkManager::handleStartRoom(int entity_id)
{
    auto entity = std::make_shared<Entity>(
        EntityType::START,
        300,
        -1,
        -1,
        -1,
        -1,
        -1,
        -1,
        ""
    );
    _entities[300] = entity;
    Logger::getInstance()->info("Handle START ROOM");
}

void NetworkManager::disconnectFromServer() {
    try {
        _clientNetwork->disconnect();
        Logger::getInstance()->info("Disconnected from server.");
    } catch (const std::exception& e) {
        Logger::getInstance()->error("Error disconnecting from server: {}", e.what());
    }
}

int NetworkManager::getClientId() {
    return _clientId;
}

const std::unordered_map<int, std::shared_ptr<Entity>>& NetworkManager::getEntities() const {
    return _entities;
}

void NetworkManager:: setEntities(std::unordered_map<int, std::shared_ptr<Entity>>& entities)
{
    _entities = entities;
}

void NetworkManager::processAsyncTasks()
{
    // mettre poll dans la fonction receiveAndDispatchUDP
    _clientNetwork->receiveAndDispatchUDP();
    _clientNetwork->poll();
}


bool NetworkManager:: getIsShootingGame()
{
    return _isShootingGame;
}
