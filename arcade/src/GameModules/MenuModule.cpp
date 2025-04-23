/*
** EPITECH PROJECT, 2020
** MenuModule
** File description:
** arcade
*/

#include <iostream>
#include "GameModules/MenuModule.hpp"

extern "C"
{
    MenuModule *entry_point()
    {
        return new MenuModule();
    }
}

MenuModule::MenuModule() : AGameModule()
{
    std::cout << "Menu loading" << std::endl;
    std::filesystem::path libPath = LIB_PATH;

    if (!std::filesystem::exists(libPath) || !std::filesystem::is_directory(libPath)) { 
        throw Exceptions::GameModule::LibFolderDoesntExist();
    }
    for (const auto& file : 
        std::filesystem::directory_iterator(libPath)) {
            std::string filepath = file.path();
        if (availableModules.find(filepath) != availableModules.end()) {
            if (availableModules.at(filepath) == GRAPHIC) {
                this->_listGraphics.push_back(filepath);
            }
            if (availableModules.at(filepath) == GAME) {
                this->_listGames.push_back(filepath);
            }
        }
    }
    this->initGame();
}

MenuModule::~MenuModule()
{
    std::cout << "Menu Unloading" << std::endl;
    this->exitGame();
}

void MenuModule::initGame()
{
    this->_status = ON;
    this->_currentGameIndex = 0;
    this->_currentGraphicIndex = 0;
    for (std::size_t i = 0; i < this->_listGames.size(); i++) {
        if (this->_listGames[i] == "./lib/arcade_menu.so") {
            this->_currentGameIndex = i;
        }
    }
    std::size_t i = 0;
    std::pair<int, int> position = std::make_pair(0, 0);

    this->_entities[i] = std::make_shared<Entity>(NameType::TEXT,
    position, std::make_pair(20, 0), "", "Games:");
    this->_entities[i]->setColor(ColorType::WHITE);
    i += 1;
    this->_currentGameIndex = i;
    this->_listGamesIndexes.first = i;
    for (const auto &game: this->_listGames) {
        position.second += 2;
        this->_entities[i] = std::make_shared<Entity>(NameType::TEXT,
        position, std::make_pair(20, 0),
        "", game);
        this->_entities[i]->setColor(ColorType::WHITE);
        i += 1;
    }
    this->_listGamesIndexes.second = i;
    position.second += 4;
    this->_entities[i] = std::make_shared<Entity>(NameType::TEXT,
    position, std::make_pair(20, 0), "", "Graphics:");
    this->_entities[i]->setColor(ColorType::WHITE);
    i += 1;
    this->_currentGraphicIndex = i;
    this->_listGraphicsIndexes.first = i;
    for (const std::string &graphic: this->_listGraphics) {
        position.second += 2;
        this->_entities[i] = std::make_shared<Entity>(NameType::TEXT, 
        position, std::make_pair(20, 0), "", graphic);
        this->_entities[i]->setColor(ColorType::WHITE);
        i += 1;
    }
    this->_listGraphicsIndexes.second = i;
    position.second += 4;
    this->_entities[i] = std::make_shared<Entity>(NameType::TEXT,
    position, std::make_pair(20, 0), "", "Username:");
    this->_entities[i]->setColor(ColorType::WHITE);
    i += 1;
    position.second += 2;
    this->_playerNameIndex = i;
    this->_entities[i] = std::make_shared<Entity>(NameType::TEXT,
    position, std::make_pair(20, 0), "", "Arcade");
    this->_entities[i]->setColor(ColorType::WHITE);
}

void MenuModule::exitGame() {}

void MenuModule::handleEvent(const Event &event)
{
    this->_status = ON;
    if (event.getEventType() == EventType::WINDOW_E) {
        if (event.getWindowEvent().getEvent() == WindowEventType::CLOSED) {
            this->_status = OFF;
        }
    }
    if (event.getEventType() == EventType::KEYBOARD) {
        this->handleSelectionGame(event);
        this->handleInputPlayerName(event);
    }
}

void MenuModule::handleSelectionGame(const Event &event)
{
    std::size_t oldIndexGame = 0;
    std::size_t oldIndexGraphic = 0;

    if (event.getKeyboardEvent().getInput() == KeyboardEventType::NEXT_GAME) {
        // std::cout << "GET EVENT KEYBOARD NEW GAME" << std::endl;
        this->_status = LOADING_NEW_GAME;
    }
    if (event.getKeyboardEvent().getInput() == KeyboardEventType::NEXT_GRAPHICAL) {
        this->_status = LOADING_NEW_DISPLAY;
    }
    if (event.getKeyboardEvent().getInput() == KeyboardEventType::UP) {
        // std::cout << "GET EVENT KEYBOARD NEXT GAME" << std::endl;
        oldIndexGame = this->_currentGameIndex;
        this->_currentGameIndex = (oldIndexGame + 1 < this->_listGamesIndexes.second) ?
            oldIndexGame + 1 : this->_listGamesIndexes.first;
        // here
        this->_status = SELECT_NEXT_GAME;
        this->_entities[oldIndexGame]->setColor(ColorType::WHITE);
        this->_entities[_currentGameIndex]->setColor(ColorType::YELLOW);
    }
    if (event.getKeyboardEvent().getInput() == KeyboardEventType::DOWN) {
        // std::cout << "GET EVENT KEYBOARD NEXT GRAPHIC" << std::endl;
        oldIndexGraphic = this->_currentGraphicIndex;
        this->_currentGraphicIndex = (oldIndexGraphic + 1 < this->_listGraphicsIndexes.second) ? 
            oldIndexGraphic + 1 : this->_listGraphicsIndexes.first;
        this->_status = SELECT_NEXT_GRAPHIC;
        this->_entities[oldIndexGraphic]->setColor(ColorType::WHITE);
        this->_entities[this->_currentGraphicIndex]->setColor(ColorType::YELLOW);
    }
    if (event.getKeyboardEvent().getInput() == KeyboardEventType::EXIT) {
        this->_status = OFF;
    }
}

void MenuModule::handleInputPlayerName(const Event &event)
{
    if (this->_alphabetLetters.find(event.getKeyboardEvent().getInput()) !=
        this->_alphabetLetters.end()) {
        std::string name = this->_entities[this->_playerNameIndex]->getText() + this->_alphabetLetters.at(event.getKeyboardEvent().getInput());
        this->_entities[this->_playerNameIndex]->setText(name);
        // std::cout << "NEW NAME " << this->_entities[this->_playerNameIndex]->getText() << std::endl;
    }
}

std::map<std::size_t, std::shared_ptr<Entity>> MenuModule::getEntities() const
{
    return (this->_entities);
}

void MenuModule::setEntities(std::map<std::size_t, std::shared_ptr<Entity>>) {}

Event& MenuModule::getEvent()
{
    return (this->_event);
}

void MenuModule::setStatus(GameStatus status)
{
    this->_status = status;
}

void MenuModule::setEvent(Event &event)
{
    this->_event = event;
}

GameStatus MenuModule::getStatus() const 
{
    return (this->_status);
}