/*
** EPITECH PROJECT, 2024
** AEntity
** File description:
** Arcade
*/

#include "Entities/Entity.hpp"

Entity::Entity(NameType nameType, const std::pair<int, int> &position, const std::pair<int, int> &dimensions,
const std::string &texture, const std::string &text)
{
    this->_nameType = nameType;
    this->_position = position;
    this->_dimensions = dimensions;
    this->_texture = texture;
    this->_text = text;
}

NameType Entity::getNameType() const
{
    return this->_nameType;
}

std::pair<int, int> Entity::getPosition() const
{
    return this->_position;
}

std::pair<int, int> Entity::getDimensions() const
{
    return this->_dimensions;
}

std::string Entity::getText() const 
{
    return this->_text;
}

std::string Entity::getTexture() const
{
    return this->_texture;
}

ColorType Entity::getColor() const 
{
    return this->_color;
}

int Entity::getSize() const 
{
    return this->_size;
}

void Entity::setPosition(std::pair <int, int>& position) 
{
    this->_position = position;
}

void Entity::setTexture(const std::string &texture) 
{
    this->_texture = texture;
}

void Entity::setText(std::string& text) 
{
    this->_text = text;
}

void Entity::setMap(std::vector<std::string> map)
{
    this->_map = map;
}

std::vector<std::string> Entity::getMap() const
{
    return this->_map;
}

void Entity::setColor(ColorType color)
{
    this->_color = color;
}