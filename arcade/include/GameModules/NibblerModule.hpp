/*
** EPITECH PROJECT, 2024
** nibbler.hpp
** File description:
** Arcade
*/

#ifndef __NIBBLER_GAME_HPP__
    #define __NIBBLER_GAME_HPP__

#include <iostream>
#include <ncurses.h>
#include <vector>
#include <deque>
#include "Event/KeyboardEvent.hpp"
#include "../GameModules/AGameModule.hpp"

#define SPRITE_WIDTH 100
#define SPRITE_HEIGHT 150
#define SNAKE_INITIAL_POS_X 11
#define SNAKE_INITIAL_POS_Y 9
#define WIDTH_MAP 33
#define HEIGHT_MAP 22

std::vector<std::string> initialMap =
{
    "################################",
    "#    o          o          o   #",
    "#  ######    ######    ######  #",
    "#    o          o          o   #",
    "#  ######    ######    ######  #",
    "#  #           o            #  #",
    "#  #  #####  ######  #####  #  #",
    "#     #      #    #      #     #",
    "#     #      ######      #     #",
    "# o      o     oo    o       o #",
    "#     #      ######      #     #",
    "#     #      #    #      #     #",
    "#  #  #####  ######  #####  #  #",
    "#  #            o           #  #",
    "#  ######    ######    ######  #",
    "#              o    o          #",
    "#  ######    ######    ######  #",
    "#     o         o        o     #",
    "################################"
};

class NibblerModule : public AGameModule {
private:
    std::vector<std::string> _originalMap;
    std::map<std::size_t, std::shared_ptr<Entity>> entities_;
    std::map<std::size_t, std::shared_ptr<Entity>> entities_food;
    bool gameOver_;
    int score_;
    int snakeX_;
    int snakeY_;
    std::deque<std::pair<int, int>> _nibblerBody;
    std::pair<int, int> _nibblerPos;
    std::pair<int, int> _foodPos;

public:
    NibblerModule();
    ~NibblerModule();
    void initGame() override;
    void exitGame() override;
    void handleEvent(const Event &event) override;
    std::map<std::size_t, std::shared_ptr<Entity>>getEntities() const override;
    void setEntities(std::map<std::size_t, std::shared_ptr<Entity>>) override;
    GameStatus getStatus() const override;
    void setStatus(GameStatus status) override;
    void setEvent(Event &event) override;
    Event &getEvent() override;
};

#endif /* __NIBBLER_GAME_HPP__ */