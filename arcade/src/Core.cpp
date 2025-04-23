/*
** EPITECH PROJECT, 2024
** Core
** File description:
** Arcade
*/

#include "Core.hpp"

Core::Core(const std::string &displayModuleName) :
    _currentDisplayModule(displayModuleName), _currentGameModule(""),
    _currentDisplayModuleIndex(0), _currentGameModuleIndex(0)
{
    bool libExist = false;
    // /!\ temporary, make fucntion that gets what's in inside lib folder
    // this->_listDisplayModules = { "./lib/arcade_ncurses.so", "./lib/arcade_sdl2.so",
    // "./lib/arcade_sfml.so"};
    // this->_listGameModules = {"./lib/arcade_menu.so",
    // "./lib/arcade_nibbler.so", "./lib/arcade_snake.so"};

    this->initArcade();
    for (std::size_t i = 0; i < this->_listDisplayModules.size(); i++) {
        if (this->_listDisplayModules[i] == displayModuleName) {
            this->_currentDisplayModule = this->_listDisplayModules[i];
            libExist = true;
        }
    }
    if (!libExist) {
        throw Exceptions::Core::InvalidInitialGraphicLib();
    }
    this->_currentGameModule = this->_listGameModules[this->_currentGameModuleIndex];
}

Core::~Core() {}

void Core::initArcade()
{
    std::filesystem::path libPath = LIB_PATH;

    if (!std::filesystem::exists(libPath) || !std::filesystem::is_directory(libPath)) { 
        throw Exceptions::Core::LibFolderDoesntExist();
    }
    for (const auto& file : 
        std::filesystem::directory_iterator(libPath)) { 
            std::string filepath = file.path();
        if (availableModules.find(filepath) != availableModules.end()) {
            if (availableModules.at(filepath) == GRAPHIC) {
                this->_listDisplayModules.push_back(filepath);
            }
            if (availableModules.at(filepath) == GAME) {
                this->_listGameModules.push_back(filepath);
            }
        }
    }
}

void Core::runArcade()
{
    std::cout << "Running Arcade" << std::endl;
    
    this->loadModule("./lib/arcade_menu.so", GAME);
    this->_gameModule->initGame();
    this->loadModule(this->_currentDisplayModule, GRAPHIC);

    while (this->_gameModule->getStatus() != OFF) {
        this->_displayModule->drawEntities(this->_gameModule->getEntities());
        this->_displayModule->handleEvents(this->_currentGameModule);
        this->_gameModule->handleEvent(this->_displayModule->getEvent());
        if (this->_gameModule->getStatus() == LOADING_NEW_DISPLAY) {
            this->switchModule(this->_currentDisplayModule, GRAPHIC);
        }
        if (this->_gameModule->getStatus() == LOADING_NEW_GAME) {
            this->switchModule(this->_currentGameModule, GAME);
            _displayModule->initDisplay(this->_gameModule->getEntities());
        }
        if (this->_gameModule->getStatus() == SELECT_NEXT_GRAPHIC) {
            this->_currentDisplayModuleIndex = (this->_currentDisplayModuleIndex + 1
            < this->_listDisplayModules.size()) ? this->_currentDisplayModuleIndex + 1 : 0;
            this->_currentDisplayModule = this->_listDisplayModules[this->_currentDisplayModuleIndex];
        }
        if (this->_gameModule->getStatus() == SELECT_NEXT_GAME) {
            this->_currentGameModuleIndex = (this->_currentGameModuleIndex + 1
            < this->_listGameModules.size()) ? this->_currentGameModuleIndex + 1 : 0;
            this->_currentGameModule = this->_listGameModules[this->_currentGameModuleIndex];
        }
        if (this->_gameModule->getStatus() == GameStatus::BACK_TO_MENU) {
            this->_currentDisplayModule = "./lib/arcade_menu.so";
            this->switchModule(this->_currentDisplayModule, GAME);
        }
        this->_displayModule->clearScreen();
    }
    this->unloadModule(GRAPHIC);
    this->unloadModule(GAME);
}

void Core::loadModule(const std::string &lib, ModuleType type)
{
    if (type == GAME) {
        _loaderGameModule.load(lib);
        _gameModule = std::shared_ptr<IGameModule>(_loaderGameModule.getInstance(ENTRYPOINT),
        [](IGameModule *p){ delete p; });
        _gameModule->initGame();
    }
    if (type == GRAPHIC) {
        _loaderDisplayModule.load(lib);
        _displayModule = std::shared_ptr<IDisplayModule>(_loaderDisplayModule.getInstance(ENTRYPOINT),
        [](IDisplayModule *p){ delete p; });
        _displayModule->initDisplay(this->_gameModule->getEntities());
    }
}

void Core::unloadModule(ModuleType type)
{
    if (type == GAME) {
        _gameModule->exitGame();
        _gameModule.reset();
        _loaderGameModule.unload();
    }
    if (type == GRAPHIC) {
        _displayModule->destroyRessources();
        _displayModule.reset();
        _loaderDisplayModule.unload();
    }
}

void Core::switchModule(const std::string &lib, ModuleType type)
{
    this->unloadModule(type);
    this->loadModule(lib, type);
}