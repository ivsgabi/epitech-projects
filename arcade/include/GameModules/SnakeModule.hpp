/*
** EPITECH PROJECT, 2024
** Snake.hpp
** File description:
** Arcade
*/

#ifndef __SNAKE_GAME_HPP__
    #define __SNAKE_GAME_HPP__

#include <iostream>
#include <ncurses.h>
#include <vector>
#include <list>
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
    "#                              #",
    "#                              #",
    "#                              #",
    "#                              #",
    "#                              #",
    "#                              #",
    "#                              #",
    "#                              #",
    "#                              #",
    "#                              #",
    "#                              #",
    "#                              #",
    "#                              #",
    "#                              #",
    "#              o               #",
    "#                              #",
    "#                              #",
    "################################"
};



class SnakeModule : public AGameModule {
private:
    // std::map<std::size_t, std::shared_ptr<Entity>> entities_;
    // std::map<std::size_t, std::shared_ptr<Entity>> entities_food;
    std::deque<std::pair<int, int>> _snakeBody;
    std::pair<int, int> _snakePos;
    std::pair<int, int> _foodPos;

public:
    SnakeModule();
    ~SnakeModule();
    void initGame() override;
    void exitGame() override;
    void handleEvent(const Event &event) override;
    std::map<std::size_t, std::shared_ptr<Entity>>getEntities() const override;
    GameStatus getStatus() const override;
    void setEntities(std::map<std::size_t, std::shared_ptr<Entity>>) override;
    void setStatus(GameStatus status) override;
    void setEvent(Event &event) override;
    Event &getEvent() override;
};

#endif /* __SNAKE_GAME_HPP__ */