/*
** EPITECH PROJECT, 2024
** SFMLRenderer.hpp
** File description:
** R-Type
*/

#ifndef SFML_RENDERER_HPP_
#define SFML_RENDERER_HPP_

#include <SFML/Graphics.hpp>
#include <vector>
#include <string>
#include <memory>
#include <unordered_map>
#include <stack>
#include "ARenderer.hpp"
#include "State.hpp"
#include "ConfigSummary.hpp"
#include "MenusRendering.hpp"
#include "GameRendering.hpp"
#include "../EntityClient.hpp"
#include "GameEvent.hpp"

class SFMLRenderer : public ARenderer {
    public:
        SFMLRenderer();
        ~SFMLRenderer();

        void initRenderer(const std::unordered_map<int, std::shared_ptr<Entity>>& entities) override;
        void destroyResources() override;
        void clearScreen() override;
        
        void render(std::unordered_map<int, std::shared_ptr<Entity>> entities) override;

        void handleInput(std::shared_ptr<Entity> crt_player, std::unordered_map<int, std::shared_ptr<Entity>> entities) override;
        
        int getCrtPlayerID() override;
        void setCrtPlayerID(int crtPlayerID) override;
        const AssetManager& getAssetManager() override;
        GameStateRendering getCurrentState() const override;
        GameEvent getCurrentEvent() override;
        void setCurrentEvent(const GameEvent& event) override;
        void setCurrentSubtitleEvent(const SubtitleEvent& event) override;
        void setIsShootingGame(bool isShootingGame) override;


    private:

        AssetManager _assetManager;
        sf::RenderWindow _window;
        sf::Event _event;
        int _crtplayerID;
        bool _isShootingGame;

        void pushState(GameStateRendering state);
        void popState();

        std::stack<GameStateRendering> _stateStack;
        
        std::stack<GameEvent> _eventStack;
        std::stack<SubtitleEvent> _subtitleStack;

        std::shared_ptr<GameRendering> _gameRenderer;
        std::shared_ptr<MenusRendering> _menusRenderer;

};

#endif /* !SFML_RENDERER_HPP_ */
