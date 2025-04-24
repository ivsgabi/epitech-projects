/*
** EPITECH PROJECT, 2024
** GameServer.cpp
** File description:
** R-Type
*/

// #include "server/ServerNetwork.hpp"
#include "ECS/Registry/Registry.hpp" 
#include "Logger.hpp"
#include "GameServer.hpp"
#include "Exceptions.hpp"
#include "NetworkManager.hpp"

std::atomic<bool> running(true);

asio::io_context* global_io_context = nullptr;

void signalHandler(int signal) {
    if (signal == SIGINT) {
        Logger::getInstance()->info("CTRL+C detected. Shutting down server...");
        running = false;
        if (global_io_context) {
            global_io_context->stop();
        }
    }
}

GameServer::GameServer(const std::string &configFile, int port) : _networkManager(std::make_shared<NetworkManager>(port))
{
    std::string filename = configFile;
    int len = filename.length() - 7 - 5;
    filename = filename.substr(7, len);

    std::string libraryPath = "./lib/lib" + filename + ".so";
    std::cout << libraryPath << std::endl;

    Logger::getInstance()->info("Initializing GameServer");
    this->loadGame(libraryPath);
    global_io_context = &this->_networkManager->_server->getIoContext();
    this->initHandlers();
    this->_game->initGame(configFile);
}

void GameServer::initHandlers()
{
    this->_game->registerCreateEntityHandler(
        [this](uint32_t entity_id, int entity_type, std::string text, int pos_x, int pos_y, int vel_x, int vel_y, int scale_x, int scale_y, bool is_controllable, uint32_t client_id) {
            // std::cout << "HIII" << std::endl;
            this->_networkManager->_server->sendEntityCreatePacket(entity_id, entity_type, text, pos_x, pos_y, vel_x, vel_y, scale_x, scale_y, is_controllable, client_id);
        }
    );
    this->_game->registerRemoveEntityHandler(
        [this](uint32_t entity_id, uint32_t client_id) {
            // std::cout << "HIII" << std::endl;
            this->_networkManager->_server->sendEntityRemovePacket(entity_id, client_id);
        }
    );
    this->_game->registerUpdateHandler(
        [this](uint32_t entity_id, int entity_type, int pos_x, int pos_y, int vel_x, int vel_y, int scale_x, int scale_y, bool is_firing, uint32_t client_id) {
            this->_networkManager->_server->sendStateUpdatePacket(entity_id,  entity_type,  pos_x,  pos_y,  vel_x,  vel_y,  scale_x,  scale_y,  is_firing, client_id);
        }
    );
    this->_game->registerUpdateHandler(
        [this](uint32_t entity_id, int entity_type, int pos_x, int pos_y, int vel_x, int vel_y, int scale_x, int scale_y, bool is_firing, uint32_t client_id) {
            this->_networkManager->_server->sendStateUpdatePacket(entity_id,  entity_type,  pos_x,  pos_y,  vel_x,  vel_y,  scale_x,  scale_y,  is_firing, client_id);
        }
    );
    this->_game->registerSendLevelHandler(
        [this](uint32_t entity_id, int level, uint32_t client_id) {
            this->_networkManager->_server->sendLevelPacket(entity_id, level, client_id);
        }
    );
    this->_game->registerSendScoreHandler(
        [this](uint32_t entity_id, int score, uint32_t client_id) {
            this->_networkManager->_server->sendScorePacket(entity_id, score, client_id);
        }
    );
    this->_game->registerSendDeadHandler(
        [this](uint32_t entity_id, int current_level, int score, uint32_t client_id ) {
            this->_networkManager->_server->sendDeadPacket(entity_id, current_level, score, client_id);
        }
    );
    this->_game->registerSendWonHandler(
        [this](uint32_t entity_id, int current_level, int score, uint32_t client_id) {
            this->_networkManager->_server->sendWonPacket(entity_id, current_level, score, client_id);
        }
    );  
    this->_networkManager->_server->registerCollisionHandler(
        [this](uint32_t entity_id){ this->_game->handleCollision(entity_id); }
    );
    this->_networkManager->_server->registerInputHandler(
        [this](uint32_t entity_id, int move_x, int move_y, bool firing) { 
            // std::cout << "HEY THERERERERREER" << std::endl;
            this->_game->handleInput(entity_id, move_x, move_y, firing);
        //    this->_networkManager->_server->sendStateUpdatePacket(entity_id, static_cast<int>(EntityType::PLAYER), move_x, move_y, 1, 1, 0, 0, firing);
        }
    );
    this->_networkManager->_server->registerSuccessConnectHandler(
        [this](int clientId) {
            this->_networkManager->handleConnectionSuccess(clientId);
            this->_game->createPlayer(clientId);
        }
    );
    this->_networkManager->_server->registerClientQuitHandler(
        [this](int clientId) {
            // std::cout << "HIIIII GUYS" << std::endl;
            #warning cote client faire sendQuit quand on quitte depuis menu
            // this->_game->handleQuitPlayer(clientId);
            #warning crash cote client quand on supprime entite qui quitte
            this->_networkManager->handleClientQuit(clientId);
            exit(84);
        }
    );
    this->_networkManager->_server->registerClientReadyHandler(
        [this](int clientId) {
            Logger::getInstance()->info("!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!Network manager - Client ready client_id={}", clientId);
            Logger::getInstance()->info("IN CLIENT READY NB CURRENTS CLIENTS {}", this->_networkManager->_clients.size());
            Logger::getInstance()->info("NB CURRENTS CLIENTS CONNECTED {}", this->_networkManager->_clientsReady.size());

            this->_networkManager->_clientsReady.push_back(clientId);    
            if ((this->_networkManager->_clientsReady.size() == this->_networkManager->_clients.size())) {
                Logger::getInstance()->info("GAME WILL START");
                Logger::getInstance()->error("All clients are connected.");
                this->_networkManager->_server->sendEntityCreatePacket(206, static_cast<int>(EntityType::NB_CLIENTS), "",
                this->_networkManager->_clientsReady.size(), 0, 0, 0, 0, 0, 0, 0);
                this->_networkManager->_server->sendStartRoomPacket(0, 0);

                //SEND ENEMIES
                this->_game->startGame();
            } else {
                Logger::getInstance()->info("CLIENT ID PUSHED");
                this->_networkManager->_server->sendEntityCreatePacket(206, static_cast<int>(EntityType::NB_CLIENTS), "", this->_networkManager->_clientsReady.size(), 0, 0, 0, 0, 0, 0, 0);
                // this->_server->sendEntityCreatePacket()
            }
        }
    );
}

GameServer::~GameServer()
{
    Logger::getInstance()->info("Destroying GameServer");
}

void GameServer::runGameLoop()
{
    std::signal(SIGINT, signalHandler);
    try {
        this->_networkManager->initConnection();

        Logger::getInstance()->info("Starting server loop...");
        while (running) {
            this->_networkManager->processAsyncTasks();
            Logger::getInstance()->debug("Running game logic...");

            this->_game->updateGame();
        }
        Logger::getInstance()->info("Stopping server...");
    } catch (const std::exception& e) {
        Logger::getInstance()->error("Server encountered an error: {}", e.what());
    }
    Logger::getInstance()->info("Exiting server.");
}

void GameServer::loadGame(const std::string &game)
{
    Logger::getInstance()->info("Loading " + game + " game ...");
    this->_loaderGame.load(game);
    this->_game = std::shared_ptr<IGame>(this->_loaderGame.getInstance(ENTRYPOINT),
        [](IGame *p){ delete p; });
}

void GameServer::unloadGame()
{
    Logger::getInstance()->info("Unloading current game ...");
    this->_game->exitGame();
    this->_game.reset();
    this->_loaderGame.unload();
}

void GameServer::switchGame(const std::string &game)
{
    Logger::getInstance()->info("Switching to " + game + " game ...");
    this->unloadGame();
    this->loadGame(game);
}