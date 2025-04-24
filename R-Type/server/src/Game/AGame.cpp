/*
** EPITECH PROJECT, 2024
** AGame.cpp
** File description:
** R-Type
*/

#include "Game/AGame.hpp"

AGame::AGame()
{
}

void AGame::registerUpdateHandler(UpdateStateHandler handler)
{
    _updateStateHandler = std::move(handler);
}

void AGame::registerCreateEntityHandler(CreateEntityHandler handler)
{
    _createEntityHandler = std::move(handler);
}

void AGame::registerRemoveEntityHandler(RemoveEntityHandler handler)
{
    _removeEntityHandler = std::move(handler);
}

void AGame::registerSendLevelHandler(SendLevelHandler handler)
{
    _sendLevelHandler = std::move(handler);
}

void AGame::registerSendScoreHandler(SendScoreHandler handler) 
{
    _sendScoreHandler = std::move(handler);
}

void AGame::registerSendDeadHandler(SendDeadHandler handler) 
{
    _sendDeadHandler = std::move(handler);
}

void AGame::registerSendWonHandler(SendWonHandler handler) 
{
    _sendWonHandler = std::move(handler);
}

// NetworkManager &AGame::getNetworkManager()
// {
//     return this->_networkManager;
// }

// Registry &AGame::getRegistry()
// {
//     return this->_registry;
// }
