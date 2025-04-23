/*
** EPITECH PROJECT, 2024
** Core.hpp
** File description:
** Arcade
*/

#ifndef CORE_HPP_
#define CORE_HPP_
#include <memory>
#include <vector>
#include <unistd.h>
#include <unordered_map>
#include "GameModules/IGameModule.hpp"
#include "DisplayModules/IDisplayModule.hpp"
#include "DLLoader.hpp"
#include "Exceptions/Exceptions.hpp"
#include "ListModules.hpp"
#define ENTRYPOINT "entry_point"

/*!
    Class handling communication between IDisplayModule and IGameModule
*/
class Core {
    public:
        Core(const std::string &displayModuleName);
        ~Core();
        void runArcade();
        void loadModule(const std::string &lib, ModuleType type);
        void unloadModule(ModuleType type);
        void switchModule(const std::string &lib, ModuleType type);
        void initArcade();

    private:
        std::shared_ptr<IGameModule> _gameModule;
        std::shared_ptr<IDisplayModule> _displayModule;
        DLLoader<IGameModule> _loaderGameModule;
        DLLoader<IDisplayModule> _loaderDisplayModule;
        std::string _currentDisplayModule;
        std::string _currentGameModule;
        std::vector<std::string> _listGameModules;
        std::vector<std::string> _listDisplayModules;
        std::size_t _currentDisplayModuleIndex;
        std::size_t _currentGameModuleIndex;
        int _score;
};

#endif /* !CORE_HPP_ */ 
