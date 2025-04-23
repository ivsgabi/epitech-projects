/*
** EPITECH PROJECT, 2024
** ADisplayModule
** File description:
** Arcade
*/

#ifndef ADISPLAY_MODULE_HPP_
#define ADISPLAY_MODULE_HPP_
#include "IDisplayModule.hpp"
#include "Exceptions/Exceptions.hpp"

class ADisplayModule : public IDisplayModule {
public:
    ADisplayModule();
    virtual ~ADisplayModule() = default;
    void setEntities(std::map<std::size_t, std::shared_ptr<Entity>> entities) final;

protected:
    std::map<std::size_t, std::shared_ptr<Entity>> _entities;
    Event _event;
};

#endif /* !ADISPLAY_MODULE_HPP_ */
