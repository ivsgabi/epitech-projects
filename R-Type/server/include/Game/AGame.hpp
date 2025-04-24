/*
** EPITECH PROJECT, 2024
** AGame.hpp
** File description:
** R-Type
*/

#ifndef AGAME_HPP_
#define AGAME_HPP_
#include "IGame.hpp"
#include "ECS/Registry/Registry.hpp"
#include "ECS/Systems/Systems.hpp"
#include "EventManager.hpp"
// #include "NetworkManager.hpp"

enum EVENT_TYPE {
    BOSS_DEFEATED,
};

class AGame: public IGame {
    public:
        AGame();
        virtual ~AGame() = default;
        // NetworkManager &getNetworkManager() override;
        void registerUpdateHandler(UpdateStateHandler handler) override;
        void registerCreateEntityHandler(CreateEntityHandler handler) override;
        void registerRemoveEntityHandler(RemoveEntityHandler handler) override;
        // virtual Registry &getRegistry() override;
        void registerSendLevelHandler(SendLevelHandler handler) override;
        void registerSendScoreHandler(SendScoreHandler handler) override;
        void registerSendDeadHandler(SendDeadHandler handler) override;
        void registerSendWonHandler(SendWonHandler handler) override;

    protected:
        ECS::Registry _registry;
        // ECS::Systems _systems;
        // NetworkManager _networkManager;
        UpdateStateHandler _updateStateHandler;
        CreateEntityHandler _createEntityHandler;
        RemoveEntityHandler _removeEntityHandler;
        SendLevelHandler _sendLevelHandler;
        SendScoreHandler _sendScoreHandler;
        SendDeadHandler _sendDeadHandler;
        SendWonHandler _sendWonHandler;
};

#endif /* !AGAME_HPP_ */
