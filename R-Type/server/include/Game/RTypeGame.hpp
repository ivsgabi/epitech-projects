/*
** EPITECH PROJECT, 2024
** RTypeGame
** File description:
** RType
*/

#ifndef RTYPE_GAME_HPP_
#define RTYPE_GAME_HPP_
#include "Game/AGame.hpp"
#include "ECS/Systems/Systems.hpp"
#include "ECS/Configuration/Parsing.hpp"
#include <unordered_map>
#define NB_LEVELS 4
#define BOSS_PV 5
#include <random>

#define BOSS_DEFEATED "BOSS_DEFEATED"
#define BOSS_TOUCHED "BOSS_TOUCHED"
#define WIN "WIN"
#define LOSE "LOSE"

#define DEFAULT_POS_PLAYER_X 200
#define DEFAULT_POS_PLAYER_Y 200
#define DEFAULT_VELOCITY_X -10
#define DEFAULT_VELOCITY_Y -10
#define DEFAULT_VELOCITY_PLAYER_X 5
#define DEFAULT_VELOCITY_PLAYER_Y 5
#define DEFAULT_SCALE_X 1
#define DEFAULT_SCALE_Y 1
#define DEFAULT_FPS 60

class RTypeGame: public AGame {
    public:
        RTypeGame();
        ~RTypeGame();
        void initGame(const std::string &configFile) override;
        void exitGame() override;
        void updateGame() override;
        void handleCollision(uint32_t entity_id) override;
        void handleInput(uint32_t entity_id, int move_x, int move_y, bool firing) override;
        void createPlayer(uint32_t clientId) override;
        void startGame() override;
        void initAssets() override;
        void sendAssets() override;
        void initAsset(const std::string &assetName, const std::string &assetPath, EntityType type) override;
        void sendEnemiesLevel() override;
        void incrementNbDamagesBoss();
        void handleQuitPlayer(int clientId) override;
        // using UpdateStateHandler = std::function<void(uint32_t, int, int, bool)>;

    private:
        // std::unordered_map<std::string, entity_t> _assets;
        std::unordered_map<uint32_t, entity_t> _players;
        // std::unordered_map<uint32_t, std::vector<entity_t>> _levels;
        // std::unordered_map<uint32_t, std::vector<entity_t>> _enemies;
        // std::unordered_map<entity_t, std::unique_ptr<position>> _movements;
        std::unordered_map<size_t, entity_t> _bossesPerLevel;
        std::unordered_map<uint32_t, std::string> _playersSprites;
        int _currentScore = 0;
        uint32_t _currentLevel = 1;
        uint32_t _nbCurrentPlayers = 0;
        uint32_t _nbDamagesBoss = 0;
        // int _enemyPositionTick = -1; 
        bool _playing = false;
        bool _figthingBoss = false;
        std::unordered_map<size_t, size_t> _levelsScoring;

        // void initMenu();
        std::vector<std::string> _assetsEnemy;
        std::vector<std::string> _assetsBosses;
        void initEnemies();
        void moveEnemies();
        // void setEnemiesLevel(size_t level);
        // entity_t initButton(std::string str);
        // entity_t initText(std::string str);
        void initPlayers();
        void initNextLevel(uint32_t entity_id);
        // entity_t initBoss(struct position pos, struct velocity velo, int scoreEnemy, size_t nbLevel, const std::string &assetPath);
        // entity_t initEnemy(struct position pos, struct velocity velo, int scoreEnemy, size_t nbLevel, const std::string &assetPath);
        void handleCollisionBoss(uint32_t entity_id);
        
        // entity_t initPlayer(struct position position, struct velocity velocity);
        std::chrono::_V2::system_clock::time_point _lastTime;
        float _frameDuration;
        float _deltaTime;
        std::random_device _rd;
        std::mt19937 _gen;
        std::shared_ptr<EventManager<RTypeGame>> _eventManager;
        // UpdateStateHandler _updateHandler;
};

#endif /* !RTYPE_GAME_HPP_ */
