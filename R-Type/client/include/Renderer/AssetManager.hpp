/*
** EPITECH PROJECT, 2024
** AssetManager.hpp
** File description:
** AssetManager
*/

#ifndef ASSETMANAGER_HPP_
#define ASSETMANAGER_HPP_

#include <unordered_map>
#include <string>
#include <SFML/Graphics.hpp>
#include <memory>
#include "../EntityClient.hpp"
#include "DefaultValues.hpp"

class Texture {
    public:
        Texture() : _recX(0), _recY(0), _scX(0), _scY(0), _nbFrame(0) {}
        Texture(const sf::Texture& text, int recX = 0, int recY = 0, float scX = 0, float scY = 0, int nbFrame = 0)
            : _texture(text), _recX(recX), _recY(recY), _scX(scX), _scY(scY), _nbFrame(nbFrame) {}

        const sf::Texture& getTexture() const { return _texture; }
        int getRecX() const { return _recX; }
        int getRecY() const { return _recY; }
        float getScX() const { return _scX; }
        float getScY() const { return _scY; }
        int getNbFrame() const {return _nbFrame;}

    private:
        sf::Texture _texture;
        int _recX;
        int _recY;
        float _scX;
        float _scY;
        int _nbFrame;
};

class AssetManager {
    public:
        AssetManager() = default;

        void loadAssetsFromEntities(const std::unordered_map<int, std::shared_ptr<Entity>>& entities);
        void loadDefaultAssets();

        const std::unordered_map<std::string, Texture>& getPlayerTextures() const;
        const std::unordered_map<std::string, Texture>& getEnemyTextures() const;
        const std::unordered_map<std::string, Texture>& getShootTextures() const;
        const std::unordered_map<std::string, sf::Texture>& getMenuTexture() const;
        const std::unordered_map<std::string, sf::Texture>& getBackgroundTextures() const;
        const std::unordered_map<std::string, Texture>& getDecorTextures() const;
        const std::unordered_map<std::string, Texture>& getLevelTextures() const;

        const sf::Font& getFont() const;
        const sf::Font& getSubtitleFont() const;
        const std::vector<std::string>& getTextOptions() const;

    private:
        std::unordered_map<std::string, sf::Texture> _menuTexture;
        std::unordered_map<std::string, sf::Texture> _backgroundTextures;
        std::unordered_map<std::string, Texture> _decorTextures;
        std::unordered_map<std::string, Texture> _levelTextures;
        std::unordered_map<std::string, Texture> _playerTextures;
        std::unordered_map<std::string, Texture> _enemyTextures;
        std::unordered_map<std::string, Texture> _shootTextures;

        sf::Font _subtitleFont;
        sf::Font _font;
        std::vector<std::string> _menuOptions;

        void loadTexture(const std::string& path, sf::Texture& texture, const std::string& defaultPath);
};


#endif /* !ASSETMANAGER_HPP_ */
