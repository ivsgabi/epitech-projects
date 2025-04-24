/*
** EPITECH PROJECT, 2024
** BackgroundSystem
** File description:
** BackgroundSystem
*/

#ifndef BACKGROUNDSYSTEM_HPP_
#define BACKGROUNDSYSTEM_HPP_

#include <SFML/Graphics.hpp>
#include "AssetManager.hpp"

class BackgroundSystem {
    public:
        BackgroundSystem(
            std::unordered_map<std::string, sf::Texture> backgroundTextures, 
            std::unordered_map<std::string, Texture> decorTextures);
        ~BackgroundSystem() = default;

        void init(const std::string& background, const std::string& decor);
        void renderBackground(sf::RenderWindow& window);
        void renderDecor(sf::RenderWindow& window);
        void update();

    private:
        std::unordered_map<std::string, sf::Texture> _backgroundTextures;
        std::unordered_map<std::string, Texture> _decorTextures;

        sf::Sprite _bgSprite1;
        sf::Sprite _bgSprite2;
        float _bgSpeed = -3.0f;

        sf::Sprite _decorsSprite1;
        sf::Sprite _decorsSprite2;
        float _decorsSpeed = -2.5f;
        int _screenWidth = 1920;
};

#endif /* !BACKGROUNDSYSTEM_HPP_ */
