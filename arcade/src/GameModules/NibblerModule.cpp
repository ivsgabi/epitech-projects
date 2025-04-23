/*
** EPITECH PROJECT, 2024
** nibbler.cpp
** File description:
** Arcade
*/

#include "GameModules/NibblerModule.hpp"
#include <cstdlib>
#include <filesystem>
#include <time.h>

const int WIDTH = 30;
const int HEIGHT = 20;

extern "C"
{
    NibblerModule *entry_point()
    {
        return new NibblerModule();
    }
}

NibblerModule::NibblerModule() : AGameModule()
{
    //std::cout << "nibbler loading" << std::endl;
}

NibblerModule::~NibblerModule()
{
    //std::cout << "nibbler Unloading" << std::endl;
    //this->exitGame();
}

void NibblerModule::initGame()
{
    srand((unsigned) time(NULL));
    this->_status = ON;
    this->_nibblerPos = std::make_pair(11, 9);
    this->_nibblerBody.push_front(_nibblerPos);
    std::size_t i = 0;
    this->_entities[i] = std::make_shared<Entity>(NameType::MAP,
    std::make_pair(0, 0), std::make_pair(0, 0), "", "");

    std::vector<std::string> map = initialMap;
    this->_originalMap = map;

    this->_foodPos = std::make_pair(-1, -1);
    this->_entities[i]->setMap(map);

    i += 1;
    this->_entities[i] = std::make_shared<Entity>(NameType::SPRITE,
    _nibblerPos, std::make_pair(SPRITE_HEIGHT, SPRITE_WIDTH), "./assets/snake.png", "S");
    i += 1;
    this->_entities[i] = std::make_shared<Entity>(NameType::SPRITE,
    std::make_pair(0, 0), std::make_pair(SPRITE_HEIGHT, SPRITE_WIDTH), "./assets/food.png", "o");
    i += 1;
    this->_entities[i] = std::make_shared<Entity>(NameType::SPRITE,
    std::make_pair(0, 0), std::make_pair(SPRITE_HEIGHT, SPRITE_WIDTH), "./assets/wall.png", "#");
    i += 1;
    this->_entities[i] = std::make_shared<Entity>(NameType::SPRITE,
    std::make_pair(0, 0), std::make_pair(SPRITE_HEIGHT, SPRITE_WIDTH), "./assets/background.png", " ");
}


void NibblerModule::handleEvent(const Event &event)
{
    this->_status = ON;
    std::pair<int, int> oldPos = this->_nibblerPos;

    if (event.getEventType() == EventType::WINDOW_E) {
        if (event.getWindowEvent().getEvent() == WindowEventType::CLOSED) {
            this->_status = OFF;
        }
    }
    if (event.getEventType() == EventType::KEYBOARD) {
        int newPosX = this->_nibblerPos.first;
        int newPosY = this->_nibblerPos.second;

        if (event.getKeyboardEvent().getInput() == KeyboardEventType::UP) {
            newPosX -= 1;
        }
        if (event.getKeyboardEvent().getInput() == KeyboardEventType::DOWN) {
            newPosX += 1;
        }
        if (event.getKeyboardEvent().getInput() == KeyboardEventType::LEFT) {
            newPosY -= 1;
        }
        if (event.getKeyboardEvent().getInput() == KeyboardEventType::RIGHT) {
            newPosY += 1;
        }
        if (event.getKeyboardEvent().getInput() == KeyboardEventType::EXIT) {
            this->_status = GameStatus::OFF;
            return;
        }
        if (event.getKeyboardEvent().getInput() == KeyboardEventType::GO_BACK_MENU) {
            this->_status = GameStatus::BACK_TO_MENU;
            return;
        }
        bool hasFood = false;

        for (const std::string &line : this->_entities[0]->getMap()) {
            if (line.find('o') != std::string::npos) {
                hasFood = true;
                break;
            }
        }
    
        if (!hasFood) {
            // Si toute la nourriture a été consommée, restaurer la carte d'origine
            this->_entities[0]->setMap(this->_originalMap);
        }
        if (newPosX >= 0 && newPosX < HEIGHT_MAP && newPosY >= 0 && newPosY < WIDTH_MAP &&
            this->_entities[0]->getMap()[newPosX][newPosY] != '#') {
            if (this->_entities[0]->getMap()[newPosX][newPosY] == 'o')
                this->_nibblerBody.push_back(oldPos);

            for (const auto &bodyPos : this->_nibblerBody) {
                if (bodyPos == std::make_pair(newPosX, newPosY)) {
                    this->_status = GameStatus::OFF;
                    return;
                }
            }
            this->_nibblerPos.first = newPosX;
            this->_nibblerPos.second = newPosY;
            this->_entities[1]->setPosition(this->_nibblerPos);

            for (auto &bodyPos : this->_nibblerBody) {
                std::pair<int, int> currentPos = bodyPos;
                bodyPos = oldPos;
                oldPos = currentPos;
            }
            std::vector<std::string> newMap = this->_entities[0]->getMap();
            newMap[oldPos.first][oldPos.second] = ' ';
            newMap[this->_nibblerPos.first][this->_nibblerPos.second] = 'S';
            this->_entities[0]->setMap(newMap);
        }
    }
}

std::map<std::size_t, std::shared_ptr<Entity>> NibblerModule::getEntities() const
{
    return (this->_entities);
}

void NibblerModule::setEntities(std::map<std::size_t, std::shared_ptr<Entity>>) {}

void NibblerModule::setEvent(Event &event)
{
    this->_event = event;
}

void NibblerModule::exitGame() {}

void NibblerModule::setStatus(GameStatus status)
{
    this->_status = status;
}

Event& NibblerModule::getEvent()
{
    return (this->_event);
}

GameStatus NibblerModule::getStatus() const
{
    //std::cout << "Nibbler Unloading" << std::endl;
    return (this->_status);
}


