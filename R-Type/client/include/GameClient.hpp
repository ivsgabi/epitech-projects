/*
** EPITECH PROJECT, 2024
** GameClient.hpp
** File description:
** R-Type
*/

#ifndef GAME_CLIENT_HPP_
#define GAME_CLIENT_HPP_

#include <iostream>
#include <memory>
#include <map>
#include "DLLoader.hpp"
#include "Audio/IAudio.hpp"
#include "Renderer/IRenderer.hpp"
#include "NetworkManagerClient.hpp"
#include "EntityClient.hpp"

#define ENTRYPOINT "entry_point"
#define LIB_AUDIO "./lib/libSFMLRenderer.so"
#define LIB_GRAPHIC "./lib/libSFMLAudio.so"

class GameClient {
    public:
        GameClient(const std::string& ip_adress, int port);
        ~GameClient();

        void connectServer();
        void loadObjects();
        int runGameLoop();
        void destroyObjects();

    private:
        void handleBackgroundMusic();
        void handleSoundOfEvents();
        void setPlayerID(int id);
        void updateEntities(std::unordered_map<int, std::shared_ptr<Entity>>& entities);
        void handleCollisions(std::unordered_map<int, std::shared_ptr<Entity>>& entities);
        void sendPlayerUpdates(std::shared_ptr<Entity> player);

        std::shared_ptr<IAudio> _audio;
        std::shared_ptr<IRenderer> _renderer;
        std::shared_ptr<NetworkManager> _networkManager;
        DLLoader<IRenderer> _loaderRenderer;
        DLLoader<IAudio> _loaderAudio;

        GameStateRendering _previousState;
        
        bool _isSound = true;
        int _playerID;
        int _score;
        bool _is_ready;
};

#endif /* !GAME_CLIENT_HPP_ */
