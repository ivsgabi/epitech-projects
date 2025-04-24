/*
** EPITECH PROJECT, 2024
** IGame.hpp
** File description:
** R-Type
*/

#ifndef IGAME_HPP_
#define IGAME_HPP_
#include "../ECS/Registry/Registry.hpp"
// #include "NetworkManager.hpp"
#include <chrono>
#include <thread>

#define WINDOW_WIDTH 1920
#define WINDOW_HEIGHT 1080

using UpdateStateHandler = std::function<void(uint32_t, int, int, int, int, int, int, int, bool, uint32_t)>;
using CreateEntityHandler = std::function<void(uint32_t, int, std::string, int , int , int , int , int , int , bool , uint32_t )>;
using RemoveEntityHandler = std::function<void(uint32_t, uint32_t)>;
using SendLevelHandler = std::function<void(uint32_t, int, uint32_t)>;
using SendScoreHandler = std::function<void(uint32_t, int, uint32_t)>;
using SendDeadHandler = std::function<void(uint32_t, int, int, uint32_t)>;
using SendWonHandler = std::function<void(uint32_t, int, int, uint32_t)>;

//      void sendLevelPacket(uint32_t entity_id, int level, uint32_t client_id = 0);
//     void sendScorePacket(uint32_t entity_id, int score, uint32_t client_id = 0);
//     void sendDeadPacket(uint32_t entity_id, int current_level, int score, uint32_t client_id = 0);
//     void sendWonPacket(uint32_t entity_id, int current_level, int score, uint32_t client_id = 0);


class IGame {
    public:
        virtual ~IGame() = default;
        virtual void initGame(const std::string &configFile) = 0;
        virtual void exitGame() = 0;
        virtual void updateGame() = 0;
        virtual void handleCollision(uint32_t entity_id) = 0;
        virtual void handleInput(uint32_t entity_id, int move_x, int move_y, bool firing) = 0;
        virtual void registerUpdateHandler(UpdateStateHandler handler) = 0;
        virtual void registerCreateEntityHandler(CreateEntityHandler handler) = 0;
        virtual void registerRemoveEntityHandler(RemoveEntityHandler handler) = 0;
        virtual void registerSendLevelHandler(SendLevelHandler handler) = 0;
        virtual void registerSendScoreHandler(SendScoreHandler handler) = 0;
        virtual void registerSendDeadHandler(SendDeadHandler handler) = 0;
        virtual void registerSendWonHandler(SendWonHandler handler) = 0;
        virtual void handleQuitPlayer(int clientId) = 0;

        virtual void createPlayer(uint32_t clientId) = 0;
        virtual void startGame() = 0;
        virtual void initAsset(const std::string &assetName, const std::string &assetPath, EntityType type) = 0;
        virtual void initAssets() = 0;
        virtual void sendAssets() = 0;
        virtual void sendEnemiesLevel() = 0;
        // virtual NetworkManager &getNetworkManager() = 0;
        // virtual void handleInput() = 0;
        // virtual Registry &getRegistry() = 0;
};

#endif /* !IGAME_HPP_ */
