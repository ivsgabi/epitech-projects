/*
** EPITECH PROJECT, 2024
** IGameModule
** File description:
** Arcade
*/

#ifndef IGAME_MODULE_HPP_
#define IGAME_MODULE_HPP_
#include <map>
#include <string>
#include <memory>
#include "../Event/Event.hpp"
#include "Entities/Entity.hpp"

enum GameStatus {
    ON,
    OFF,
    LOADING_NEW_DISPLAY,
    LOADING_NEW_GAME,
    BACK_TO_MENU,
    SELECT_NEXT_GRAPHIC,
    SELECT_NEXT_GAME,
};

class IGameModule {
    public:
        virtual ~IGameModule() = default;
        virtual void initGame() = 0;
        virtual void exitGame() = 0;
        virtual void handleEvent(const Event &event) = 0;
        virtual std::map<std::size_t, std::shared_ptr<Entity>>getEntities() const = 0;
        virtual void setEntities(std::map<std::size_t, std::shared_ptr<Entity>>) = 0;
        virtual GameStatus getStatus() const = 0;
        virtual void setStatus(GameStatus status) = 0;
        virtual void setEvent(Event &event) = 0;
        virtual Event &getEvent() = 0;
};

#endif /* !IGAME_MODULE_HPP_ */
