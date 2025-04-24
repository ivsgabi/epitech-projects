/*
** EPITECH PROJECT, 2024
** IRenderer.hpp
** File description:
** R-Type
*/

#ifndef IRENDERER_HPP_
#define IRENDERER_HPP_

    #include <unordered_map>
    #include <memory>
    #include <string>
    #include <iostream>
    #include "../EntityClient.hpp"
    #include "State.hpp"
    #include "GameEvent.hpp"
    #include "AssetManager.hpp"

class IRenderer {
    public:
        virtual ~IRenderer() = default;
        virtual void initRenderer(const std::unordered_map<int, std::shared_ptr<Entity>>& entities) = 0;
        virtual void destroyResources() = 0;
        virtual void clearScreen() = 0;
        virtual void render(std::unordered_map<int, std::shared_ptr<Entity>> entities) = 0;
        virtual void handleInput(std::shared_ptr<Entity> crt_player, std::unordered_map<int, std::shared_ptr<Entity>> entities) = 0;

        // mettre dans ARENDERER
        virtual void setIsShootingGame(bool isShootingGame) = 0;
        virtual int getCrtPlayerID() = 0;
        virtual void setCrtPlayerID(int crtPlayerID) = 0;
        virtual const AssetManager& getAssetManager() = 0;
        virtual GameStateRendering getCurrentState() const = 0;
        virtual GameEvent getCurrentEvent() = 0;
        virtual void setCurrentEvent(const GameEvent& event) = 0;
        virtual void setCurrentSubtitleEvent(const SubtitleEvent& event) = 0;
};

#endif /* !IRENDERER_HPP_ */
