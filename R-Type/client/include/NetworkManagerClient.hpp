/*
** EPITECH PROJECT, 2024
** NetworkManager.hpp
** File description:
** NetworkManager
*/

#ifndef NETWORKMANAGER_HPP_
#define NETWORKMANAGER_HPP_

    #include <memory>
    #include <iostream>
    #include <unordered_map>
    #include "client/ClientNetwork.hpp"
    #include "EntityClient.hpp"

    #define IP_ADR "127.0.0.1"
    #define PORT 4242

class NetworkManager {
    public:
        NetworkManager(const std::string& host, int port);
        ~NetworkManager();

        void connectToServer(const std::string& name);
        void disconnectFromServer();
        void sendInputPacket(int entity_id, int move_x, int move_y, bool firing);
        void sendCollisionPacket(int entity_id, int enemy_id);
        void sendQuitPacket();
        void sendReadyPacket();
        void processAsyncTasks();

        const std::unordered_map<int, std::shared_ptr<Entity>>& getEntities() const;
        void setEntities(std::unordered_map<int, std::shared_ptr<Entity>>& entities);
        int getClientId();
        bool getIsShootingGame();

    private:
        void handleConnectionSuccess(int clientId);


        void handleStateUpdate(int entityId, int entityType, int posX, int posY, int velX, int velY, int scaleX, int scaleY, bool isFiring);
        void handleSuccessDisconnect();
        void handleEntityCreate(int entityId, int entityType, const std::string& text, int posX, int posY, int velX, int velY, int scaleX, int scaleY, bool isControllable);
        void handleEntityRemove(int entity_id);
        
        void handleScore(int entity_id, int score);
        void handleWon(int entity_id, int current_level, int score);
        void handleDead(int entity_id, int current_level, int score);
        void handleLevel(int entity_id, int level);
        void handleStartRoom(int entity_id);
    
        int _clientId = -1;
        bool _isShootingGame = false;
        std::shared_ptr<ClientNetwork> _clientNetwork;
        std::unordered_map<int, std::shared_ptr<Entity>> _entities;
};

#endif /* !NETWORKMANAGER_HPP_ */
