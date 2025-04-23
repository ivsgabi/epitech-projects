/*
** EPITECH PROJECT, 2024
** ADisplayModule.cpp
** File description:
** Arcade
*/

#include "DisplayModules/ADisplayModule.hpp"

ADisplayModule::ADisplayModule()
{
    
}

void ADisplayModule::setEntities(std::map<std::size_t, std::shared_ptr<Entity>> entities)
{
    this->_entities = entities;
}