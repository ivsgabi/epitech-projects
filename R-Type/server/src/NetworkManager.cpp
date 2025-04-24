/*
** EPITECH PROJECT, 2024
** NetworkManager.cpp
** File description:
** R-Type
*/

#include "NetworkManager.hpp"
#include "ECS/Entity/Entity.hpp"

NetworkManager::NetworkManager(int port): _server(std::make_shared<ServerNetwork>(port))
{
    // this->_server->registerSuccessConnectHandler(
    //     [this](int clientId) {
    //         handleConnectionSuccess(clientId);
            
    //     }
    // );
    // this->_server->registerInputHandler(
    //     [this]() { handleInput(); }
    // );
    // this->_server->registerCollisionHandler(
    //     [this]() { collisionHandler_(); }
    // );
    // this->_server->
    // this->_server->registerClientReadyHandler(
    //     [this](int clientId) {
    //         handleClientReady(clientId);
    //     }
    // );
}

NetworkManager::~NetworkManager()
{
}

void NetworkManager::initConnection()
{
    this->_server->receiveAndDispatchUDP();
}

void NetworkManager::handleConnectionSuccess(int clientId)
{
    Logger::getInstance()->info("Network manager - New client connected client_id={}", clientId);
    if (this->_clients.size() == MAX_CLIENTS) {
        Logger::getInstance()->error("The room is full");
    } else {
        this->_clients.push_back(clientId);
        Logger::getInstance()->info("NEW CLIENT HOLAAA");
    }
    Logger::getInstance()->info("NB CURRENTS CLIENTS {}", this->_clients.size());
    Logger::getInstance()->info("IN CONNECT SUCCESS NB CURRENT CLIENTS CONNECTED {}", this->_clientsReady.size());
}

void NetworkManager::handleClientReady(int clientId)
{
    // Logger::getInstance()->info("!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!Network manager - Client ready client_id={}", clientId);
    // Logger::getInstance()->info("IN CLIENT READY NB CURRENTS CLIENTS {}", this->_clients.size());
    // Logger::getInstance()->info("NB CURRENTS CLIENTS CONNECTED {}", this->_clientsReady.size());

    // this->_clientsReady.push_back(clientId);    
    // if ((this->_clientsReady.size() == this->_clients.size())) {
    //     Logger::getInstance()->info("GAME WILL START");
    //     Logger::getInstance()->error("All clients are connected.");
    //     this->_server->sendEntityCreatePacket(206, static_cast<int>(EntityType::NB_CLIENTS), "", this->_clientsReady.size(), 0, 0, 0, 0, 0, 0, 0);
    //     this->_server->sendStartRoomPacket(0, 0);
    // } else {
    //     Logger::getInstance()->info("CLIENT ID PUSHED");
    //     this->_server->sendEntityCreatePacket(206, static_cast<int>(EntityType::NB_CLIENTS), "", this->_clientsReady.size(), 0, 0, 0, 0, 0, 0, 0);
    //     // this->_server->sendEntityCreatePacket()
    // }
}

void NetworkManager::handleClientQuit(int clientId)
{
    Logger::getInstance()->info("CALLED HANDLE QUIT");
    for (int i = 0; i < this->_clientsReady.size(); i++){
        if (this->_clientsReady[i] == clientId){
            this->_clientsReady.erase(this->_clientsReady.begin() + i);
            break;
        }
    }
    for (int i = 0; i < this->_clients.size(); i++){
        if (this->_clients[i] == clientId){
            this->_clients.erase(this->_clients.begin() + i);
            break;
        }
    }
}

// std::vector<int> NetworkManager::getClients() const
// {
//     return this->_clients;
// }

// std::vector<int> NetworkManager::getClientsReady() const
// {
//     return this->_clientsReady;
// }

// void NetworkManager::handleInput()
// {
    
// }

void NetworkManager::registerCollisionHandler(CollisionHandler handler)
{
    collisionHandler_ = std::move(handler);
}
  
// void NetworkManager::receive()
// {
// }

// void NetworkManager::send(const Packet &packet)
// {
    
// }

void NetworkManager::processAsyncTasks()
{
    this->_server->getIoContext().poll();
}