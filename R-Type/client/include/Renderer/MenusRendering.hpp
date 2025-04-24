/*
** EPITECH PROJECT, 2025
** MenusRendering.hpp
** File description:
** MenusRendering
*/

#ifndef MENUSRENDERING_HPP
#define MENUSRENDERING_HPP

#include <SFML/Graphics.hpp>
#include <stack>
#include <unordered_map>
#include <memory>
#include <iostream>
#include "../EntityClient.hpp"
#include "State.hpp"
#include "AssetManager.hpp"
#include "MenuSystem.hpp"
#include "AssetPlayerSelection.hpp"
#include "ConfigSummary.hpp"
#include "../../../networking/include/Logger.hpp"


class MenusRendering {
    public:
        MenusRendering(AssetManager& assetManager, std::stack<GameStateRendering>& stateStack);
        ~MenusRendering() = default;

        void initialize();

        void render(GameStateRendering crtState, sf::RenderWindow& window, const std::unordered_map<int, std::shared_ptr<Entity>>& entities);
        void handleInput(GameStateRendering crtState, const sf::Event& event, std::shared_ptr<Entity> crt_player);

    private:
        void renderMenu(sf::RenderWindow& window);
        void renderMenuOpt(sf::RenderWindow& window);
        void renderHelp(sf::RenderWindow& window);
        void renderAssetPlayer(sf::RenderWindow& window);
        void renderLevels(sf::RenderWindow& window);
        void renderAccept(sf::RenderWindow& window, const std::unordered_map<int, std::shared_ptr<Entity>>& entities);
        void renderConfigSummary(sf::RenderWindow& window, const std::unordered_map<int, std::shared_ptr<Entity>>& entities);

        void handleMenuInput(const sf::Event& event);
        void handleMenuOptInput(const sf::Event& event, std::shared_ptr<Entity> crt_player);
        void handleHelpInput(const sf::Event& event);
        void handleAssetPlayerInput(const sf::Event& event);
        void handleLevelsInput(const sf::Event& event);
        void handleConfigSummaryInput(const sf::Event& event);

        AssetManager& _assetManager;
        std::stack<GameStateRendering>& _stateStack;

        std::shared_ptr<MenuSystem> _menu1System;
        std::shared_ptr<MenuSystem> _menu2System;
        std::shared_ptr<AssetPlayerSelection> _levelsSelection;
        std::shared_ptr<AssetPlayerSelection> _assetsSelection;
        std::shared_ptr<ConfigSummary> _configSummary;

        sf::RectangleShape _blurOverlay;
        sf::Sprite _shortcutSprite;
        sf::Texture _shortcutTexture;
};

#endif // MENUSRENDERING_HPP

