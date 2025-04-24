/*
** EPITECH PROJECT, 2024
** ConfigSummary.hpp
** File description:
** ConfigSummary
*/

#ifndef CONFIGSUMMARY_HPP_
#define CONFIGSUMMARY_HPP_

#include <SFML/Graphics.hpp>
#include <string>
#include <unordered_map>
#include <memory>
#include "AssetManager.hpp"
#include "../EntityClient.hpp"

class ConfigSummary {
    public:
        ConfigSummary(const sf::Font& font, const sf::Texture& bg, const std::unordered_map<std::string, Texture>& textures);
        ~ConfigSummary() = default;

        void init();
        void setConfig(const std::string& path);
        void render(sf::RenderWindow& window, std::unordered_map<int, std::shared_ptr<Entity>> entities, int lobby);
        void handleInput(const sf::Event& event, bool& confirmed, bool& back);


    private:
        sf::Texture _bgTexture;
        sf::Sprite _bgSprite;
        sf::Font _font;
        sf::Text _titleText;
        sf::Text _confirmButton;
        sf::Text _backButton;
        sf::RectangleShape _confirmBorder;
        sf::RectangleShape _backBorder;

        const std::unordered_map<std::string, Texture>& _textures;
        std::vector<sf::Sprite> _configSprites;
        bool _confirmSelected = true;

        void updateSelection(bool confirm);
};

#endif /* !CONFIGSUMMARY_HPP_ */
