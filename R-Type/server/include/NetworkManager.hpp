/*
** EPITECH PROJECT, 2024
** NetworkManager.hpp
** File description:
** R-Type
*/

#ifndef NETWORK_MANAGER_HPP_
#define NETWORK_MANAGER_HPP_
#include "server/ServerNetwork.hpp"
#define MAX_CLIENTS 4

class NetworkManager {
    public:
        NetworkManager(int port = 4242);
        ~NetworkManager();
        void initConnection();
        void handleConnectionSuccess(int clientId);
        void handleClientReady(int clientId);
        void handleClientQuit(int clientId);
        // void handleInput();
        // void handleCollision();
        // void sendToClient(uint32_t client_id);
        // void broadcast();
        // void receive();
        void processAsyncTasks();
        std::shared_ptr<ServerNetwork> _server;
        // std::vector<int> getClients() const;
        // std::vector<int> getClientsReady() const;
        using CollisionHandler = std::function<void()>;
        void registerCollisionHandler(CollisionHandler handler);
        std::vector<int> _clients;
        std::vector<int> _clientsReady;

    protected:
    private:
        CollisionHandler collisionHandler_;
};

#endif /* !NETWORK_MANAGER_HPP_ */
