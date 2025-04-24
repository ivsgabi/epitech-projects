/*
** EPITECH PROJECT, 2024
** GameServer.hpp
** File description:
** R-Type
*/

#ifndef GAME_SERVER_HPP_
#define GAME_SERVER_HPP_

#include <memory>
#include "Game/IGame.hpp"
#include "Physics.hpp"
#include "DLLoader.hpp"
#include "NetworkManager.hpp"
#define ENTRYPOINT "entry_point"
#define SUCCESS 0
#define ERROR 84

class GameServer {
    public:
        GameServer(const std::string &configFile, int port = 4242);
        ~GameServer();
        void initHandlers();
        void runGameLoop();
        void loadGame(const std::string &game);
        void unloadGame();
        void switchGame(const std::string &game);

    private:
        std::shared_ptr<IGame> _game;
        DLLoader<IGame> _loaderGame;
        std::shared_ptr<NetworkManager> _networkManager;
};

#endif /* !GAME_SERVER_HPP_ */
