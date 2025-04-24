#include "Game/FlappyBirdGame.hpp"

extern "C"
{
    FlappyBirdGame *entry_point()
    {
        return new FlappyBirdGame();
    }
} // SAME

void goNextLevelCallback(FlappyBirdGame *game)
{
    //std::cout << "IN CALLBACK" << std::endl;
    game->sendEnemiesLevel();
    // exit(84);
} // SAME

void handleBossHitCallback(FlappyBirdGame *game) {
    //std::cout << "IN CALLBACK BOSS DAMAGES" << std::endl;
    game->incrementNbDamagesBoss();
    // exit(84);
}  // SAME

FlappyBirdGame::FlappyBirdGame() : _gen(_rd()), _eventManager(std::make_shared<EventManager<FlappyBirdGame>>())
{
    std::cout << "This is FlappyBird Game module" << std::endl;
    this->_eventManager->on(BOSS_DEFEATED, goNextLevelCallback);
    this->_eventManager->on(BOSS_TOUCHED, handleBossHitCallback);
    this->_lastTime = std::chrono::high_resolution_clock::now();
    this->_frameDuration = 1.0f / DEFAULT_FPS; 
}  // SAME

FlappyBirdGame::~FlappyBirdGame() {
    //std::cout << "FlappyBirdGame destructor called." << std::endl;
    this->exitGame();
}  // SAME

void FlappyBirdGame::initGame(const std::string &configFile) {
    ECS::Configuration::Parsing parser(configFile);
    //std::cout << "Init FlappyBird Game" << std::endl;
    parser.initECSFromFile(this->_registry);
}  // SAME

void FlappyBirdGame::exitGame() {
    //std::cout << "In FlappyBird exitGame()" << std::endl;
} 

void FlappyBirdGame::updateGame() {
    auto currentTime = std::chrono::high_resolution_clock::now();
    std::chrono::duration<float> elapsedTime = currentTime - this->_lastTime;
    this->_deltaTime = elapsedTime.count();

    if (this->_playing && this->_deltaTime >= this->_frameDuration) {
        this->moveEnemies();
        this->_lastTime = currentTime;
    }
    if (this->_currentScore < 0) {
        this->_sendDeadHandler(0, this->_currentLevel, 0, 0);
    }
    if (this->_playing) {
    }
    std::this_thread::sleep_for(std::chrono::milliseconds(1));
}

void FlappyBirdGame::handleCollision(uint32_t entity_id) {}

void FlappyBirdGame::createPlayer(uint32_t clientId)
{
    this->sendAssets();
    auto &players = this->_registry.get_components<is_player>();
    auto &positions = this->_registry.get_components<position>();
    auto &velocities = this->_registry.get_components<velocity>();
    auto &assets = this->_registry.get_components<has_asset>();
    auto createdPlayer = -1;

    for (size_t entityId = 0; entityId < players.size(); entityId++) {
        auto player = players[entityId];

        if (player && player->nb <= this->_nbCurrentPlayers) {
            auto assetCurrentPlayer = assets[entityId];
            auto positionCurrentPlayer = positions[entityId];
            auto velocityCurrentPlayer = velocities[entityId];
            _createEntityHandler(entityId, static_cast<int>(EntityType::PLAYER), assetCurrentPlayer->asset, positionCurrentPlayer->x,
                positionCurrentPlayer->y, velocityCurrentPlayer->vx, velocityCurrentPlayer->vy, 0, 0, false, clientId); // envoyer les clients deja presents juste au nouveau client plutot
        }
        if (player) {
        }
        if (player && player->nb == this->_nbCurrentPlayers + 1) {
            createdPlayer = entityId;
            //std::cout << "AYOOOOOOOOOOOOOOO " << createdPlayer << std::endl;
        }
    }
    this->_nbCurrentPlayers += 1;
    this->_players[clientId] = createdPlayer;
    if (createdPlayer == -1) {
        exit(84);
    }
    auto assetCreatedPlayer = assets[createdPlayer];
    auto positionCreatedPlayer = positions[createdPlayer];
    auto velocityCreatedPlayer = velocities[createdPlayer];

    _createEntityHandler(createdPlayer, static_cast<int>(EntityType::ME), assetCreatedPlayer->asset, positionCreatedPlayer->x,
            positionCreatedPlayer->y, velocityCreatedPlayer->vx, velocityCreatedPlayer->vy, 0, 0, false, clientId);
    
    for (auto &[otherClientId, entityId]: this->_players) {
        //std::cout << "SEND NEW PLAYER TO OTHER " << std::endl;
        if (clientId != otherClientId) {
            _createEntityHandler(createdPlayer, static_cast<int>(EntityType::PLAYER), assetCreatedPlayer->asset, positionCreatedPlayer->x,
                positionCreatedPlayer->y, velocityCreatedPlayer->vx, velocityCreatedPlayer->vy, 0, 0, false, otherClientId);
        }
    }
}

void FlappyBirdGame::initAssets() {}

void FlappyBirdGame::initAsset(const std::string &assetName, const std::string &assetPath, EntityType type) {} // #warning remove initAsset from IGame

void FlappyBirdGame::handleInput(uint32_t entity_id, int move_x, int move_y, bool firing) 
{
    auto allEnemies = this->_registry.get_components<is_enemy>();
    auto allPositions = this->_registry.get_components<position>();
    auto velocityPlayer = this->_registry.get_components<velocity>()[entity_id];
    auto allSizes = this->_registry.get_components<size>();

    auto birdPosition = allPositions[entity_id];
    if (!birdPosition) {
        return;
    }
    for (size_t i = 0; i < allEnemies.size() && i < allPositions.size(); i++) {
        auto const& isEnemy = allEnemies[i];
        auto const& pos = allPositions[i];
        auto const& sizeEnemy = allSizes[i];
        // if (isEnemy && pos) {
        //     if (handleCollision(birdPosition.value(), pos.value())) {
        //         this->_currentScore = 0;
        //         return;
        //     }
        // }
        // std::cout << "POS ENEMY" << pos->x << " " << pos->y << std::endl;
        // if (pos->x <= move_x && move_x <= pos->x + sizeEnemy->x &&
        //     pos->y <= move_y && move_y <= pos->y + sizeEnemy->y) {
        //     this->_currentScore -= 1;
        //     this->_sendScoreHandler(0, this->_currentScore, 0);
        // }
    }
    // if (birdPosition->y < 0 || birdPosition->y > WINDOW_HEIGHT) {
    //     this->_currentScore = 0;
    //     return;
    // }
    this->_updateStateHandler(entity_id, static_cast<int>(EntityType::PLAYER), move_x, move_y, velocityPlayer->vx, velocityPlayer->vy,
        1, 1, firing, 0);
}


void FlappyBirdGame::startGame() {
    this->_sendScoreHandler(0, this->_currentScore, 0);
    this->sendEnemiesLevel();
    auto &levels = this->_registry.get_components<level>();
    auto &assets = this->_registry.get_components<has_asset>();
    for (size_t entityId = 0; entityId < levels.size(); entityId++) {
        if (levels[entityId] && assets[entityId] && assets[entityId]->type == EntityType::BACKGROUND) {
            this->_createEntityHandler(entityId, static_cast<int>(EntityType::BACKGROUND), assets[entityId]->asset, 0, 0, 0, 0, 1, 1, false, 0);
            //std::cout << "HEYREEEEEEEEEEEEEEE 1" << std::endl;
            break;
            // exit(84);
        }
    }
    this->_playing = true;
    #warning background à chaque level, FAIRE CONDITIONS LOSE
}

void FlappyBirdGame::sendAssets() { 
    auto &assets = this->_registry.get_components<has_asset>();
    auto &rectAnimations = this->_registry.get_components<rect_animation>();

    for (size_t entityId = 0; entityId < assets.size(); entityId++) {
        auto &asset = assets[entityId];
        auto &rectAnimation = rectAnimations[entityId];

        if (asset && asset->type == EntityType::ASSET_PLAYER || asset->type == EntityType::ASSET_ENEMY ||
                 asset->type == EntityType::ASSET_LEVELS) {
            //std::cout << "SENDING ASSET PLAYER OR ENEMY" << std::endl;
            auto rectAnimationData = this->_registry.get_components<rect_animation>()[entityId];
            auto scaleAsset = this->_registry.get_components<scale>()[entityId];
            this->_createEntityHandler(entityId, static_cast<int>(asset->type), asset->asset, rectAnimationData->x,
                                       rectAnimationData->y, rectAnimationData->nbFrames, 0, scaleAsset->sx, scaleAsset->sy, 0, 0);
        } else if (asset && asset->type == EntityType::ASSET_DECOR) {
            //std::cout << "SEND DECOR" << std::endl;
            auto scaleAsset = this->_registry.get_components<scale>()[entityId];
            this->_createEntityHandler(entityId, static_cast<int>(asset->type), asset->asset, 1,
                                       1, 0, 0, scaleAsset->sx, scaleAsset->sy, 0, 0);
        } else if (asset && (asset->type == EntityType::ASSET_BACKGROUND || asset->type == EntityType::BACKGROUND_MENU ||
            asset->type == EntityType::FONT || asset->type == EntityType::LOGO)) {
            //std::cout << "SENDING OTHER TYPE OF ASSETS" << std::endl;
            this->_createEntityHandler(entityId, static_cast<int>(asset->type), asset->asset, 0, 0, 0, 0, 0, 0, 0, 0);
        }
    }
}

void FlappyBirdGame::sendEnemiesLevel() {
    //std::cout << "SEND ENEMIES LEVEL " << _currentLevel << std::endl;
    this->_sendLevelHandler(0, this->_currentLevel, 0);
    
    auto &enemiesPerLevel = this->_registry.get_components<level>();
    auto &positions = this->_registry.get_components<position>();
    auto &velocities = this->_registry.get_components<velocity>();
    auto assets = this->_registry.get_components<has_asset>();
    // auto bosses = this->_registry.get_components<is_boss>();

    for (size_t entityId = 0; entityId < enemiesPerLevel.size(); entityId++) {
        if (positions[entityId] && assets[entityId] && enemiesPerLevel[entityId]->level == this->_currentLevel) {
            auto positionEnemy = positions[entityId];
            auto assetEnemy = assets[entityId];

            //std::cout << "HERE!!! -> ENEMY POS: " << positionEnemy->x << " " << positionEnemy->y << std::endl;
            this->_createEntityHandler(entityId, static_cast<int>(EntityType::ENEMY), assetEnemy->asset, positionEnemy->x,
                    positionEnemy->y, 0, 0, DEFAULT_SCALE_X, DEFAULT_SCALE_Y, false, 0);
        }
    }
}

void FlappyBirdGame::incrementNbDamagesBoss() {
    this->_nbDamagesBoss += 1;
}

void FlappyBirdGame::moveEnemies() { // obstacles
    auto &enemiesPerLevel = this->_registry.get_components<level>();
    auto &positions = this->_registry.get_components<position>();
    auto &velocities = this->_registry.get_components<velocity>();
    auto &enemies = this->_registry.get_components<is_enemy>();

    for (size_t entityId = 0; entityId < enemiesPerLevel.size(); entityId++) {
        if (positions[entityId] && velocities[entityId] && enemiesPerLevel[entityId]->level == this->_currentLevel
            && enemies[entityId]) {
            auto &positionEnemy = positions[entityId];
            auto &velocityEnemy = velocities[entityId];

            positionEnemy->x += velocityEnemy->vx;
            //std::cout << "position ENEMY x -> "<< positionEnemy->x << std::endl;

            if (positionEnemy->x + 20 <= 0) {
                positionEnemy->x = WINDOW_WIDTH;
                // positionEnemy->y = pick value from value list;
            }
            this->_updateStateHandler(entityId, static_cast<int>(EntityType::ENEMY),
                                      positionEnemy->x, positionEnemy->y, velocityEnemy->vx, velocityEnemy->vy,
                                      1, 1, false, 0);
        }
    }
}

void FlappyBirdGame::initNextLevel(uint32_t entity_id) {
    this->_removeEntityHandler(entity_id, 0);
    this->_nbDamagesBoss = 0;
    this->_figthingBoss = false;

    auto &levels = this->_registry.get_components<level>();
    auto &enemies = this->_registry.get_components<is_enemy>();
    //auto &bosses = this->_registry.get_components<is_boss>();

    for (size_t entityId = 0; entityId < levels.size(); entityId++) {
        if (levels[entityId]->level == this->_currentLevel && enemies[entityId]) {
            this->_removeEntityHandler(entityId, 0);
        }
    }
    this->_currentLevel += 1;
    //std::cout << "CURRENT LEVEL " << _currentLevel << std::endl;
    if (this->_currentLevel > NB_LEVELS) {
        //std::cout << "YOU WON" << std::endl;
        this->_sendWonHandler(entity_id, this->_currentLevel - 1, this->_currentScore, 0);
        this->_playing = false;
    }
    this->_eventManager->emit(BOSS_DEFEATED, this);
}

void FlappyBirdGame::handleCollisionBoss(uint32_t entity_id) {
    //std::cout << "BOSS TOUCHED " << std::endl;
    auto bossPV = this->_registry.get_components<is_boss>()[entity_id];
    this->_eventManager->emit(BOSS_TOUCHED, this);
    // exit(84);
    if (this->_nbDamagesBoss >= bossPV->pv) {
        //std::cout << "BOSS DEFEATED LEVEL " << this->_currentLevel << std::endl;
        this->initNextLevel(entity_id);
    }
}

void FlappyBirdGame::handleQuitPlayer(int clientId) {}