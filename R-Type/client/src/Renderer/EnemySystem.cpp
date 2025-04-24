/*
** EPITECH PROJECT, 2024
** EnemySystem
** File description:
** EnemySystem
*/

#include "Renderer/EnemySystem.hpp"
#include "../../../networking/include/Logger.hpp"

EnemySystem::EnemySystem(const std::unordered_map<std::string, Texture>& enemyTextures)
    : _enemyTextures(enemyTextures) {}

static std::string trimNulls(const std::string& str)
{
    size_t end = str.find_last_not_of('\0');
    return str.substr(0, end + 1); 
}

void EnemySystem::render(sf::RenderWindow& window, std::shared_ptr<Entity> entity)
{
    std::string path = trimNulls(entity->getContent());
    if (_enemyTextures.find(path) != _enemyTextures.end()) {
        _enemySprite.setTexture(_enemyTextures.at(path).getTexture());
        _enemySprite.setTextureRect(sf::IntRect(
                0,
                0,
                _enemyTextures.at(path).getRecX(),
                _enemyTextures.at(path).getRecY()
        ));
        _enemySprite.setScale(_enemyTextures.at(path).getScX(), _enemyTextures.at(path).getScY());
        _enemySprite.setPosition(entity->getX(), entity->getY());
        Logger::getInstance()->info("Rendering enemy at position ({}, {})", entity->getX(), entity->getY());
        window.draw(_enemySprite);
    } else {
        Logger::getInstance()->error("Enemy texture not found for path: {}.", path);
    }
}
