/*
** EPITECH PROJECT, 2024
** Entity.cpp
** File description:
** Entity
*/

#include "EntityClient.hpp"

Bullet::Bullet(int x, int y, int speedX, int speedY) : _x(x), _y(y), _speedX(speedX), _speedY(speedY) {}

int Bullet::getX() const
{ 
    return _x; 
}

int Bullet::getY() const 
{ 
    return _y; 
}

void Bullet::move() 
{
    _x += _speedX;
    _y += _speedY;
}

bool Bullet::isOutOfBounds(int screenWidth, int screenHeight) const 
{
    return _x < 0 || _x > screenWidth || _y < 0 || _y > screenHeight;
}


Entity::Entity(EntityType type, int id, float x, float y, float vel_x, float vel_y,float sc_x, float sc_y, std::string content)
        : _type(type), _id(id), _x(x), _y(y), _vel_x(vel_x), _vel_y(vel_y), _sc_x(sc_x), _sc_y(sc_y), _isShooting(false), _content(content) {}

Entity::~Entity() {};

EntityType Entity:: getType() {
    return _type;
};

float Entity:: getX() {
    return _x;
};

float Entity:: getY()  {
    return _y;
};

float Entity:: getVel_x()  {
    return _vel_x;
};

float Entity:: getVel_y()  {
    return _vel_y;
};

float Entity:: getSc_x()  {
    return _sc_x;
};

float Entity:: getSc_y()  {
    return _sc_y;
};

int Entity:: getId() {
    return _id;
};

void Entity:: setType(EntityType type)  {
    _type = type;
};

void Entity:: setX(float x) {
    _x = x;
};

void Entity:: setY(float y) {
    _y = y;
};

void Entity:: setVel_x(float vel_x) {
    _vel_x = vel_x;
};

void Entity:: setVel_y(float vel_y) {
    _vel_y = vel_y;
};

void Entity:: setSc_x(float sc_x) {
    _sc_x = sc_x;
};

void Entity:: setSc_y(float sc_y) {
    _sc_y = sc_y;
};

void Entity:: setId(int id) {
    _id = id;
};

bool Entity:: getIsShooting() {
    return _isShooting;
}

void Entity:: setIsShooting(bool isShooting) {
    _isShooting = isShooting;
}

std::string Entity:: getContent() {
    return _content;
}

void Entity:: setContent(std::string content) {
    _content = content;
}

std::vector<Bullet>& Entity::getBullets()
{ 
    return _bullets;
    }

void Entity::addBullet(int x, int y, int speedX, int speedY)
{
    _bullets.emplace_back(x, y, speedX, speedY);
}
