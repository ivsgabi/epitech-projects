/*
** EPITECH PROJECT, 2024
** IDisplayModule
** File description:
** Arcade
*/

#ifndef IDISPLAY_MODULE_HPP_
#define IDISPLAY_MODULE_HPP_
#include <map>
#include <string>
#include <memory>
#include "Event/Event.hpp"

class IDisplayModule {
    public:
        virtual ~IDisplayModule() = default;
        virtual void initDisplay(std::map<std::size_t, std::shared_ptr<Entity>> entities) = 0;
        virtual void destroyRessources() = 0;
        virtual void clearScreen() = 0;
        virtual void drawEntities(std::map<std::size_t, std::shared_ptr<Entity>> entities) = 0;
        virtual void handleEvents(const std::string &crtGameLib) = 0;
        virtual Event &getEvent() = 0;
        virtual void setEntities(std::map<std::size_t, std::shared_ptr<Entity>> entities) = 0;
};

#endif /* !IDISPLAY_MODULE_HPP_ */
