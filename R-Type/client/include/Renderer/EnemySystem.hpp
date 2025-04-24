/*
** EPITECH PROJECT, 2024
** EnemySystem
** File description:
** EnemySystem
*/

#ifndef ENEMYSYSTEM_HPP_
#define ENEMYSYSTEM_HPP_

#include <SFML/Graphics.hpp>
#include <unordered_map>
#include <memory>
#include "../EntityClient.hpp"
#include "AssetManager.hpp"

class EnemySystem {
    public:
        EnemySystem(const std::unordered_map<std::string, Texture>& enemyTextures);
        ~EnemySystem() = default;

        void render(sf::RenderWindow& window, std::shared_ptr<Entity> entity);

    private:
        const std::unordered_map<std::string, Texture>& _enemyTextures;
        sf::Sprite _enemySprite;
};

#endif /* !ENEMYSYSTEM_HPP_ */


