/*
** EPITECH PROJECT, 2024
** AssetPlayerSelection.hpp
** File description:
** AssetPlayerSelection
*/

#ifndef ASSETPLAYERSELECTION_HPP_
#define ASSETPLAYERSELECTION_HPP_

#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>
#include <unordered_map>
#include "AssetManager.hpp"
#include "State.hpp"
#include "BasicComp.hpp"

class AssetPlayerSelection {
    public:
        AssetPlayerSelection(const sf::Font& font, const sf::Texture& background, const std::unordered_map<std::string, Texture>& assetsSelection);
        ~AssetPlayerSelection();

        void render(sf::RenderWindow& window);
        void handleInput(const sf::Event& event);
        bool getConfirmed();
        void resetConfirmed();
        const Texture& getSelectedAsset() const;

    private:
        sf::Sprite _bg;
        const std::unordered_map<std::string, Texture>& _assetsTextures;
        std::vector<sf::Sprite> _assetsSprites;
        std::vector<sf::RectangleShape> _assetsBorders;

        sf::Text _titleText;
        sf::Text _instructionText;
        sf::ConvexShape _arrow;

        size_t _currentSelection;
        bool _confirmed = false;

        void initObjectsSelection(BasicComp& basicComp);
        void updateSelectionDisplay();
};

#endif /* !ASSETPLAYERSELECTION_HPP_ */
