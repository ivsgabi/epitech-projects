/*
** EPITECH PROJECT, 2024
** RTypeGame.cpp
** File description:
** R-Type
*/

#include "Game/RTypeGame.hpp"

extern "C"
{
    RTypeGame *entry_point()
    {
        return new RTypeGame();
    }
}

void goNextLevelCallback(RTypeGame *game)
{
    std::cout << "IN CALLBACK" << std::endl;
    game->sendEnemiesLevel();
    // exit(84);
}

void handleBossHitCallback(RTypeGame *game)
{
    std::cout << "IN CALLBACK BOSS DAMAGES" << std::endl;
    game->incrementNbDamagesBoss();
    // exit(84);
}

RTypeGame::RTypeGame() : _gen(_rd()), _eventManager(std::make_shared<EventManager<RTypeGame>>())
{
    std::cout << "This is RType Game module" << std::endl;
    // this->_eventManager->on(BOSS_DEFEATED, [this]() {
    //     this->_currentLevel += 1;
    //     std::cout << "NEXT LEVEL!!!!!!!!!!!!!!!!!!!!!!!!!!!!!! " << this->_currentLevel << std::endl;
    //     this->sendEnemiesLevel();
    //     this->_figthingBoss = false;
    // });
    this->_eventManager->on(BOSS_DEFEATED, goNextLevelCallback);
    this->_eventManager->on(BOSS_TOUCHED, handleBossHitCallback);
    this->_lastTime = std::chrono::high_resolution_clock::now();
    this->_frameDuration = 1.0f / DEFAULT_FPS; 
}

RTypeGame::~RTypeGame()
{
    std::cout << "Destroying RType Game" << std::endl;
    this->exitGame();
}

void RTypeGame::initGame(const std::string &configFile)
{
    // ECS::AssetsManager assetsManager;
    ECS::Configuration::Parsing parser(configFile);
    std::cout << "Init RType Game" << std::endl;
    // this->_registry._entitiesManager.registertAllComponent();
    parser.initECSFromFile(this->_registry);

    this->initAssets();
    this->initEnemies();
    this->initPlayers();
}

void RTypeGame::handleInput(uint32_t entity_id, int move_x, int move_y, bool firing)
{
    auto allEnemies = this->_registry.get_components<level>();
    auto allPositions = this->_registry.get_components<position>();
    auto allScores = this->_registry.get_components<score>();
    auto velocityPlayer = this->_registry.get_components<velocity>()[entity_id];
    auto allSizes = this->_registry.get_components<size>();

    for (size_t i = 0; i < allEnemies.size() && i < allPositions.size(); i++) {
        auto const& enemy = allEnemies[i];
        auto const& pos = allPositions[i];
        auto const& sizeEnemy = allSizes[i];
        if (enemy && pos && enemy->level == this->_currentLevel) {
            std::cout << "LEVEL " << enemy->level << std::endl;
            std::cout << "ENEMY POS =======>" << pos->x << " " << pos->y << std::endl;
            if (pos->x <= move_x && move_x <= pos->x + sizeEnemy->x &&
                pos->y <= move_y && move_y <= pos->y + sizeEnemy->y) {
                entity_t entityId = this->_registry._entitiesManager.entity_from_index(i);
                auto const& enemyScore = allScores[i];
                if (enemyScore) {
                    std::cout << "COLLISION DETECTED W/ ENTITY_ID -> " << entityId << std::endl;
                    std::cout << "CURRENT SCORE -> " << _currentScore << std::endl;
                    std::cout << "TOUCHED ENEMY SCORE -> " << _currentScore << std::endl;
                    _currentScore = _currentScore - enemyScore->score;
                    if (_currentScore - enemyScore->score < 0) {
                        this->_sendScoreHandler(0, 0, 0);
                    } else {
                        this->_sendScoreHandler(0, this->_currentScore, 0);
                    }
                    std::cout << "NEW SCORE -> " << _currentScore << std::endl;
                    // exit(84);
                }
            }
        }
    }
    this->_updateStateHandler(entity_id, static_cast<int>(EntityType::PLAYER), move_x, move_y, velocityPlayer->vx, velocityPlayer->vy,
        1, 1, firing, 0);
}

void RTypeGame::incrementNbDamagesBoss()
{
    this->_nbDamagesBoss += 1;
}

void RTypeGame::handleQuitPlayer(int clientId)
{
    this->_removeEntityHandler(clientId, 0);
}

void RTypeGame::sendAssets()
{
    // for (auto &[assetName, entityId]: this->_assets) {
    //     auto assetPath = this->_registry.get_components<has_asset>()[entityId];

    //     if (assetPath->type == EntityType::ASSET_SHOOT) {
    //         auto rectAnimationData = this->_registry.get_components<rect_animation>()[entityId];
    //         std::cout << "SENDING ASSET SHOOT" << rectAnimationData->x << " " << rectAnimationData->y << " " << rectAnimationData->nbFrames << std::endl;
    //         this->_createEntityHandler(entityId, static_cast<int>(assetPath->type), assetPath->asset, rectAnimationData->x,
    //             rectAnimationData->y, rectAnimationData->nbFrames, 1, 1, 1, 0, 0);
    //     } else if (assetPath->type == EntityType::ASSET_PLAYER || assetPath->type == EntityType::ASSET_ENEMY ||
    //         assetPath->type == EntityType::ASSET_OTHER || assetPath->type == EntityType::ASSET_LEVELS) {
    //         std::cout << "SENDING ASSET PLAYER OR ENEMY" << std::endl;
    //         auto rectAnimationData = this->_registry.get_components<rect_animation>()[entityId];
    //         auto scaleAsset = this->_registry.get_components<scale>()[entityId];
    //         this->_createEntityHandler(entityId, static_cast<int>(assetPath->type), assetPath->asset, rectAnimationData->x,
    //             rectAnimationData->y, rectAnimationData->nbFrames, 0, scaleAsset->sx, scaleAsset->sy, 0, 0);
    //     } else if (assetPath->type == EntityType::ASSET_DECOR) {
    //         std::cout << "SEND DECOR" << std::endl;
    //         auto scaleAsset = this->_registry.get_components<scale>()[entityId];
    //         this->_createEntityHandler(entityId, static_cast<int>(assetPath->type), assetPath->asset, 1,
    //             1, 0, 0, scaleAsset->sx, scaleAsset->sy, 0, 0);
    //     } else {
    //         std::cout << "SENDING OTHER TYPE OF ASSETS" << std::endl;
    //         this->_createEntityHandler(entityId, static_cast<int>(assetPath->type), assetPath->asset, 0, 0, 0, 0, 0, 0, 0, 0);
    //     }
    // }
    auto &assets = this->_registry.get_components<has_asset>();
    auto &rectAnimations = this->_registry.get_components<rect_animation>();

    for (size_t entityId = 0; entityId < assets.size(); entityId++) {
        auto &asset = assets[entityId];
        auto &rectAnimation = rectAnimations[entityId];

        if (asset && asset->type == EntityType::ASSET_SHOOT && rectAnimation) {
            std::cout << "SENDING ASSET SHOOT" << rectAnimation->x << " " << rectAnimation->y << " " << rectAnimation->nbFrames << std::endl;
            this->_createEntityHandler(entityId, static_cast<int>(asset->type), asset->asset, rectAnimation->x,
                                       rectAnimation->y, rectAnimation->nbFrames, 1, 1, 1, 0, 0);
        } else if (asset && asset->type == EntityType::ASSET_PLAYER || asset->type == EntityType::ASSET_ENEMY ||
                 asset->type == EntityType::ASSET_LEVELS) {
            std::cout << "SENDING ASSET PLAYER OR ENEMY" << std::endl;
            auto rectAnimationData = this->_registry.get_components<rect_animation>()[entityId];
            auto scaleAsset = this->_registry.get_components<scale>()[entityId];
            this->_createEntityHandler(entityId, static_cast<int>(asset->type), asset->asset, rectAnimationData->x,
                                       rectAnimationData->y, rectAnimationData->nbFrames, 0, scaleAsset->sx, scaleAsset->sy, 0, 0);
        } else if (asset && asset->type == EntityType::ASSET_DECOR) {
            std::cout << "SEND DECOR" << std::endl;
            auto scaleAsset = this->_registry.get_components<scale>()[entityId];
            this->_createEntityHandler(entityId, static_cast<int>(asset->type), asset->asset, 1,
                                       1, 0, 0, scaleAsset->sx, scaleAsset->sy, 0, 0);
        } else if (asset && (asset->type == EntityType::ASSET_BACKGROUND || asset->type == EntityType::BACKGROUND_MENU ||
            asset->type == EntityType::FONT || asset->type == EntityType::LOGO || asset->type == EntityType::BACKGROUND || asset->type == EntityType::IS_SHOOT)) {
            std::cout << "SENDING OTHER TYPE OF ASSETS" << std::endl;
            this->_createEntityHandler(entityId, static_cast<int>(asset->type), asset->asset, 0, 0, 0, 0, 0, 0, 0, 0);
        }
    }
}   

void RTypeGame::initAssets() {}

void RTypeGame::initAsset(const std::string &assetName, const std::string &assetPath, EntityType type) {}

void RTypeGame::initPlayers() {}


void RTypeGame::initEnemies()
{
    // std::cout << "iNIT BOSSES" << std::endl;

    auto &enemiesPerLevel = this->_registry.get_components<level>();
    auto &bosses = this->_registry.get_components<is_boss>();
    auto &enemies = this->_registry.get_components<is_enemy>();
    auto &scores = this->_registry.get_components<score>();

    for (size_t entityId = 0; entityId < bosses.size(); entityId++) {
        if (bosses[entityId] && enemiesPerLevel[entityId] && !enemies[entityId]) {
            // std::cout << "ENTITY ID " << entityId << " PV " << bosses[entityId]->pv << std::endl;
            auto levelEnemy = enemiesPerLevel[entityId];
            this->_bossesPerLevel[levelEnemy->level] = entityId;
        }
    }

    for (auto &[level, entityId]: this->_bossesPerLevel) {
        // std::cout << level << " " << entityId << " yooo " << bosses[entityId]->pv << std::endl;
    }
    for (size_t entityId = 0; entityId < enemiesPerLevel.size(); entityId++) {
        if (!bosses[entityId] && !enemies[entityId] &&
            enemiesPerLevel[entityId] && scores[entityId]) {
            auto scorePerLevel = scores[entityId];
            auto level = enemiesPerLevel[entityId]->level;
            this->_levelsScoring[level] = scorePerLevel->score;
        }
    }
}

void RTypeGame::moveEnemies()
{
    #warning make systems for move ennemies and score
    // std::cout << "UPDATE POS ENEMIES" << std::endl;

    auto &enemiesPerLevel = this->_registry.get_components<level>();
    auto &positions = this->_registry.get_components<position>();
    auto &velocities = this->_registry.get_components<velocity>();
    auto enemies = this->_registry.get_components<is_enemy>();
    auto bosses = this->_registry.get_components<is_boss>();

    for (size_t entityId = 0; entityId < enemiesPerLevel.size(); entityId++) {
        if (positions[entityId] && velocities[entityId] && enemiesPerLevel[entityId]->level == this->_currentLevel
            && enemies[entityId] && !bosses[entityId]) {
            auto &positionEnemy = this->_registry.get_components<position>()[entityId];
            auto &velocityEnemy = this->_registry.get_components<velocity>()[entityId];
            positionEnemy->x += velocityEnemy->vx;
            
            if (positionEnemy->x <= 0) {
                positionEnemy->x = WINDOW_WIDTH;
            } else if (positionEnemy->x >= WINDOW_WIDTH) {
                positionEnemy->x = 0;
            }
            this->_updateStateHandler(entityId, static_cast<int>(EntityType::ENEMY),
                positionEnemy->x, positionEnemy->y, velocityEnemy->vx, velocityEnemy->vy,
                1, 1, false, 0); 
        }
        if (positions[entityId] && velocities[entityId] &&
            enemiesPerLevel[entityId]->level == this->_currentLevel && this->_figthingBoss &&
            !enemies[entityId] && bosses[entityId]) {
            auto &positionEnemy = positions[entityId];
            auto &velocityEnemy = velocities[entityId];

            // std::cout << "BOSS LVL " <<  _currentLevel << " POS " << positionEnemy->x << " " << positionEnemy->y << std::endl;
            // std::cout << "BOSS LVL " <<  _currentLevel << " VELOC " << velocityEnemy->vx << " " << velocityEnemy->vy << std::endl;
            positionEnemy->y += velocityEnemy->vy;
            if (positionEnemy->y <= 0) {
                positionEnemy->y = WINDOW_HEIGHT;
            } else if (positionEnemy->y >= WINDOW_HEIGHT) {
                positionEnemy->y = 0;
            }
            this->_updateStateHandler(entityId, static_cast<int>(EntityType::ENEMY),
                positionEnemy->x, positionEnemy->y, velocityEnemy->vx, velocityEnemy->vy,
                1, 1, false, 0);
        }
    }
}
 
void RTypeGame::startGame()
{
    // this->initEnemies();
    
    //SEND ENEMIES
    this->_sendScoreHandler(0, this->_currentScore, 0);
    auto &levels = this->_registry.get_components<level>();
    auto &assets = this->_registry.get_components<has_asset>();
    for (size_t entityId = 0; entityId < levels.size(); entityId++) {
        if (levels[entityId] && assets[entityId] && assets[entityId]->type == EntityType::BACKGROUND) {
            this->_createEntityHandler(entityId, static_cast<int>(EntityType::BACKGROUND), assets[entityId]->asset, 0, 0, 0, 0, 1, 1, false, 0);
        }
        if (levels[entityId] && assets[entityId] && assets[entityId]->type == EntityType::DECOR) {
            this->_createEntityHandler(entityId, static_cast<int>(EntityType::DECOR), assets[entityId]->asset, 0, 0, 0, 0, 1, 1, false, 0);
        }
    }
    this->sendEnemiesLevel();
    this->_playing = true;
    
}

void RTypeGame::createPlayer(uint32_t clientId)
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
            // std::cout << "BRODACAST OTHER PLAYERS  " << std::endl;
            _createEntityHandler(entityId, static_cast<int>(EntityType::PLAYER), assetCurrentPlayer->asset, positionCurrentPlayer->x,
                positionCurrentPlayer->y, velocityCurrentPlayer->vx, velocityCurrentPlayer->vy, 0, 0, false, clientId); // envoyer les clients deja presents juste au nouveau client plutot
        }
        if (player) {
            // std::cout << "HEEEEYYYY =======>>>>> " << player->nb << std::endl;

        }
        if (player && player->nb == this->_nbCurrentPlayers + 1) {
            createdPlayer = entityId;
            // std::cout << "AYOOOOOOOOOOOOOOO " << createdPlayer << std::endl;
        }
    }
    this->_nbCurrentPlayers += 1;
    this->_players[clientId] = createdPlayer;
    if (createdPlayer == -1) {
        std::cout << "Error create player" << std::endl;
        exit(84);
    }
    auto assetCreatedPlayer = assets[createdPlayer];
    auto positionCreatedPlayer = positions[createdPlayer];
    auto velocityCreatedPlayer = velocities[createdPlayer];

    _createEntityHandler(createdPlayer, static_cast<int>(EntityType::ME), assetCreatedPlayer->asset, positionCreatedPlayer->x,
            positionCreatedPlayer->y, velocityCreatedPlayer->vx, velocityCreatedPlayer->vy, 0, 0, false, clientId);
    
    for (auto &[otherClientId, entityId]: this->_players) {
        // std::cout << "SEND NEW PLAYER TO OTHER " << std::endl;
        if (clientId != otherClientId) {
            _createEntityHandler(createdPlayer, static_cast<int>(EntityType::PLAYER), assetCreatedPlayer->asset, positionCreatedPlayer->x,
                positionCreatedPlayer->y, velocityCreatedPlayer->vx, velocityCreatedPlayer->vy, 0, 0, false, otherClientId);
        }
    }
}

void RTypeGame::initNextLevel(uint32_t entity_id)
{
    auto &levels = this->_registry.get_components<level>();
    auto &assets = this->_registry.get_components<has_asset>();
    for (size_t entityId = 0; entityId < levels.size(); entityId++) {
        if (levels[entityId] && assets[entityId] && assets[entityId]->type == EntityType::BACKGROUND
            && levels[entityId]->level == this->_currentLevel + 1) {
            this->_createEntityHandler(entityId, static_cast<int>(EntityType::BACKGROUND), assets[entityId]->asset, 0, 0, 0, 0, 1, 1, false, 0);
            // std::cout << "HEYREEEEEEEEEEEEEEE" << std::endl;
            // exit(84);
        }
        if (levels[entityId] && assets[entityId] && assets[entityId]->type == EntityType::BACKGROUND
            && levels[entityId]->level == this->_currentLevel) {
            this->_removeEntityHandler(entityId, 0);
            // std::cout << "REMOVE OLD" << std::endl;
            // exit(84);
        }
        if (levels[entityId] && assets[entityId] && assets[entityId]->type == EntityType::DECOR) {
            this->_createEntityHandler(entityId, static_cast<int>(EntityType::DECOR), assets[entityId]->asset, 0, 0, 0, 0, 1, 1, false, 0);
            // std::cout << "HEYREEEEEEEEEEEEEEE 1" << std::endl;
            // exit(84);
        }
        if (levels[entityId] && assets[entityId] && assets[entityId]->type == EntityType::DECOR
            && levels[entityId]->level == this->_currentLevel) {
            this->_removeEntityHandler(entityId, 0);
            // std::cout << "REMOVE OLD" << std::endl;
            // exit(84);
        }
    }
    this->_removeEntityHandler(entity_id, 0);
    this->_nbDamagesBoss = 0;
    this->_figthingBoss = false;

    auto &enemies = this->_registry.get_components<is_enemy>();
    auto &bosses = this->_registry.get_components<is_boss>();

    for (size_t entityId = 0; entityId < levels.size(); entityId++) {
        if (levels[entityId]->level == this->_currentLevel && enemies[entityId] && !bosses[entityId]) {
            this->_removeEntityHandler(entityId, 0);
        }
    }
    if (this->_currentLevel + 1 > NB_LEVELS) {
        // std::cout << "YOU WON" << std::endl;
        this->_sendWonHandler(entity_id, this->_currentLevel, this->_currentScore, 0);
        this->_playing = false;
    } else {
        this->_currentLevel += 1;
        //std::cout << "CURRENT LEVEL " << _currentLevel << std::endl;
        this->_eventManager->emit(BOSS_DEFEATED, this);
    }
}

void RTypeGame::handleCollisionBoss(uint32_t entity_id)
{
    // std::cout << "BOSS TOUCHED " << std::endl;
    auto bossPV = this->_registry.get_components<is_boss>()[entity_id];
    this->_eventManager->emit(BOSS_TOUCHED, this);
    // exit(84);
    if (this->_nbDamagesBoss >= bossPV->pv) {
        // std::cout << "BOSS DEFEATED LEVEL " << this->_currentLevel << std::endl;
        this->initNextLevel(entity_id);
    }
}

void RTypeGame::handleCollision(uint32_t entity_id)
{
    auto scoreEnemy = this->_registry.get_components<score>()[entity_id];
    
    if (entity_id == this->_bossesPerLevel[this->_currentLevel] && this->_figthingBoss) {
        this->handleCollisionBoss(entity_id);
    } else {
        // std::cout << "TOUCHED ENEMY WITH " << scoreEnemy->score << "POINTS " << std::endl;
        this->_currentScore += scoreEnemy->score;
        // std::cout << "!!!!!!!!!!!!!!!!!!!!!!!!!!!SCORE" << this->_currentScore;
        this->_sendScoreHandler(0, this->_currentScore, 0);
        this->_removeEntityHandler(entity_id, 0);
    }
}


void RTypeGame::exitGame() {}

void RTypeGame::sendEnemiesLevel()
{
    // std::cout << "SEND ENEMIES LEVEL " << _currentLevel << std::endl;
    // this->_sendLevelHandler(0, this->_currentLevel, 0);
    // for (auto &enemy: this->_levels.at(_currentLevel)) {
    //     auto positionEnemy = this->_registry.get_components<position>()[enemy];
    //     auto velocityEnemy = this->_registry.get_components<velocity>()[enemy];
    //     auto assetEnemy = this->_registry.get_components<has_asset>()[enemy];

    //     std::cout << "ENEMY POS " << positionEnemy->x << " " << positionEnemy->y << std::endl;
    //     this->_createEntityHandler(enemy, static_cast<int>(EntityType::ENEMY), assetEnemy->asset, positionEnemy->x,
    //             positionEnemy->y, velocityEnemy->vx, velocityEnemy->vy, DEFAULT_SCALE_X, DEFAULT_SCALE_Y, false, 0);

    // }


    // std::cout << "SEND ENEMIES LEVEL " << _currentLevel << std::endl;
    this->_sendLevelHandler(0, this->_currentLevel, 0);
    
    auto &enemiesPerLevel = this->_registry.get_components<level>();
    auto &positions = this->_registry.get_components<position>();
    auto &velocities = this->_registry.get_components<velocity>();
    auto assets = this->_registry.get_components<has_asset>();
    auto bosses = this->_registry.get_components<is_boss>();

    for (size_t entityId = 0; entityId < enemiesPerLevel.size(); entityId++) {
        if (positions[entityId] && velocities[entityId] && assets[entityId] && enemiesPerLevel[entityId]->level == this->_currentLevel
            && !bosses[entityId]) {
            auto positionEnemy = positions[entityId];
            auto velocityEnemy = velocities[entityId];
            auto assetEnemy = assets[entityId];

            //std::cout << "ENEMY POS " << positionEnemy->x << " " << positionEnemy->y << std::endl;
            this->_createEntityHandler(entityId, static_cast<int>(EntityType::ENEMY), assetEnemy->asset, positionEnemy->x,
                    positionEnemy->y, velocityEnemy->vx, velocityEnemy->vy, DEFAULT_SCALE_X, DEFAULT_SCALE_Y, false, 0);
        }
    }
}

void RTypeGame::updateGame() 
{
    auto currentTime = std::chrono::high_resolution_clock::now();
    std::chrono::duration<float> elapsedTime = currentTime - this->_lastTime;
    this->_deltaTime = elapsedTime.count();

    if (this->_currentScore >= this->_levelsScoring[this->_currentLevel] && !this->_figthingBoss) {
        // send entity boss
        auto positionEnemy = this->_registry.get_components<position>()[this->_bossesPerLevel[this->_currentLevel]];
        auto velocityEnemy = this->_registry.get_components<velocity>()[this->_bossesPerLevel[this->_currentLevel]];
        auto assetEnemy = this->_registry.get_components<has_asset>()[this->_bossesPerLevel[this->_currentLevel]];

        //std::cout << "SEND BOSS ASSET ENEMYY LVL " << _currentLevel << "POS " << positionEnemy->x << " " << positionEnemy->y << " " << assetEnemy->asset << std::endl;
        this->_createEntityHandler(this->_bossesPerLevel[this->_currentLevel], static_cast<int>(EntityType::ENEMY), assetEnemy->asset, positionEnemy->x,
                positionEnemy->y, velocityEnemy->vx, velocityEnemy->vy, 0, 0, false, 0);
        this->_figthingBoss = true;
    }
    if (this->_currentScore < 0) {
        this->_sendDeadHandler(0, this->_currentLevel, 0, 0);
    }

    if (this->_playing && this->_deltaTime >= this->_frameDuration) {
        this->moveEnemies();
        this->_lastTime = currentTime;
    }
    std::this_thread::sleep_for(std::chrono::milliseconds(1));

    if (this->_playing && this->_figthingBoss) {
        // std::cout << "FIGTHING BOSS LEVEL " << this->_currentLevel << "NB DAMAGE " << this->_nbDamagesBoss << std::endl;
        // std::cout << "NB TO BEAT IT " << this->_registry.get_components<is_boss>()[this->_bossesPerLevel[this->_currentLevel]]->pv << std::endl;
        // std::cout << "CURRENT SCORE " << _currentScore << std::endl;
    } else if (this->_playing) {
        // std::cout << "CURRENT LEVEL " << _currentLevel << std::endl;
        //     std::cout << "CURRENT SCORE " << _currentScore << std::endl;
        
    }
}
