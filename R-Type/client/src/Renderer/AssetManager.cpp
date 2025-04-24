/*
** EPITECH PROJECT, 2025
** AssetManager.cpp
** File description:
** AssetManager
*/

#include <iostream>
#include "Renderer/AssetManager.hpp"
#include "../../../networking/include/Logger.hpp"


void AssetManager::loadTexture(const std::string& path, sf::Texture& texture, const std::string& defaultPath)
{
    if (!texture.loadFromFile(path)) {
        std::cerr << "Failed to load texture: " << path << ", using default.\n";
        if (!texture.loadFromFile(defaultPath)) {
            std::cerr << "Failed to load default texture: " << defaultPath << "\n";
        }
    }
}

void AssetManager::loadDefaultAssets()
{
    sf::Texture level4;
    loadTexture(DEFAULT_LEVEL_4, level4, DEFAULT_LEVEL_4);
    _levelTextures[DEFAULT_LEVEL_4] = Texture(level4, 200, 95, 1, 1, 1);
    sf::Texture level3;
    loadTexture(DEFAULT_LEVEL_3, level3, DEFAULT_LEVEL_3);
    _levelTextures[DEFAULT_LEVEL_3] = Texture(level3, 200, 95, 1, 1, 1);
    sf::Texture level2;
    loadTexture(DEFAULT_LEVEL_2, level2, DEFAULT_LEVEL_2);
    _levelTextures[DEFAULT_LEVEL_2] = Texture(level2, 200, 95, 1, 1, 1);
    sf::Texture level1;
    loadTexture(DEFAULT_LEVEL_1, level1, DEFAULT_LEVEL_1);
    _levelTextures[DEFAULT_LEVEL_1] = Texture(level1, 200, 95, 1, 1, 1);

    if (!_subtitleFont.loadFromFile("./assets/fonts/subtitleFont.woff")) {
        std::cerr << "Failed to load font: " << "./assets/fonts/subtitleFont.ttf" << ", using default.\n";
    }

}

static std::string trimNulls(const std::string& str)
{
    size_t end = str.find_last_not_of('\0');
    return str.substr(0, end + 1);
}

void AssetManager::loadAssetsFromEntities(const std::unordered_map<int, std::shared_ptr<Entity>>& entities)
{
    loadDefaultAssets();
    Logger::getInstance()->info("LOAD ASSETS ENTITIES");
    if (entities.empty())
        Logger::getInstance()->info("ENTITIES EMPTY");
    for (const auto& [id, entity] : entities) {
        Logger::getInstance()->info("Player RECx={}, RECy={}, ScX={}, ScY={}, nbFrame={}", entity->getX(), entity->getY(), entity->getSc_x(), entity->getSc_y(), entity->getVel_x());

    }

    for (const auto& [id, entity] : entities) {
        std::string path = trimNulls(entity->getContent());

        switch (entity->getType()) {
            case EntityType::LOGO: {
                sf::Texture logoTexture;
                loadTexture(path, logoTexture, DEFAULT_LOGO_PATH);
                _menuTexture["logo"] = logoTexture;
                break;
            }
            case EntityType::BACKGROUND_MENU: {
                sf::Texture menuTexture;
                loadTexture(path, menuTexture, DEFAULT_BG_PATH);
                _menuTexture["bg-menu"] = menuTexture;
                break;
            }
            case EntityType::ASSET_PLAYER: {
                sf::Texture playerTexture;
                loadTexture(path, playerTexture, DEFAULT_PLAYER_1);
                _playerTextures[path] = Texture(playerTexture, entity->getX(), entity->getY(), entity->getSc_x(), entity->getSc_y(), entity->getVel_x());
                break;
            }
            case EntityType::ASSET_ENEMY: {
                sf::Texture enemyTexture;
                loadTexture(path, enemyTexture, DEFAULT_ENEMY_1);
                _enemyTextures[path] = Texture(enemyTexture, entity->getX(), entity->getY(), entity->getSc_x(), entity->getSc_y(), entity->getVel_x());
                break;
            }
            case EntityType::ASSET_SHOOT: {
                sf::Texture shootTexture;
                loadTexture(path, shootTexture, DEFAULT_SHOOT_1);
                _shootTextures[path] = Texture(shootTexture, entity->getX(), entity->getY(), entity->getSc_x(), entity->getSc_y(), entity->getVel_x());
                break;
            }
            case EntityType::ASSET_DECOR: {
                sf::Texture decorTexture;
                loadTexture(path, decorTexture, DEFAULT_DECOR_1);
                _decorTextures[path] = Texture(decorTexture, entity->getX(), entity->getY(), entity->getSc_x(), entity->getSc_y(), entity->getVel_x());
                break;
            }
            case EntityType::ASSET_LEVELS: {
                sf::Texture levelTexture;
                loadTexture(path, levelTexture, DEFAULT_LEVEL_1);
                _levelTextures[path] = Texture(levelTexture, entity->getX(), entity->getY(), entity->getSc_x(), entity->getSc_y(), entity->getVel_x());
                break;
            }
            case EntityType::ASSET_BACKGROUND: {
                sf::Texture bgTexture;
                loadTexture(path, bgTexture, DEFAULT_BG_PATH);
                _backgroundTextures[path] = bgTexture;
                break;
            }
            case EntityType::FONT: {
                if (!_font.loadFromFile(path)) {
                    std::cerr << "Failed to load font: " << path << ", using default.\n";
                    _font.loadFromFile(DEFAULT_FONT_PATH);
                }
                break;
            }
            default:
                break;
        }
    }
    _menuOptions = DEFAULT_OPTIONS;

    Logger::getInstance()->info("PRINT PLAYER TEXTURES");
    for (const auto& [id, texture] : _playerTextures) {
        Logger::getInstance()->info("name id {}", id);
        Logger::getInstance()->info("Player RECx={}, RECy={}, ScX={}, ScY={}, nbFrame={}", texture.getRecX(), texture.getRecY(), texture.getScX(), texture.getScY(), texture.getNbFrame());
    }

    Logger::getInstance()->info("PRINT ENEMY TEXTURES");
    for (const auto& [id, texture] : _enemyTextures) {
        Logger::getInstance()->info("name id {}", id);
        Logger::getInstance()->info("Enemy RECx={}, RECy={}, ScX={}, ScY={}, nbFrame={}", texture.getRecX(), texture.getRecY(), texture.getScX(), texture.getScY(), texture.getNbFrame());
    }

    Logger::getInstance()->info("PRINT SHOOT TEXTURES");
    for (const auto& [id, texture] : _shootTextures) {
        Logger::getInstance()->info("name id {}", id);
        Logger::getInstance()->info("Shoot RECx={}, RECy={}, ScX={}, ScY={}, nbFrame={}", texture.getRecX(), texture.getRecY(), texture.getScX(), texture.getScY(), texture.getNbFrame());
    }

    Logger::getInstance()->info("PRINT DECOR TEXTURES");
    for (const auto& [id, texture] : _decorTextures) {
        Logger::getInstance()->info("name id {}", id);
        Logger::getInstance()->info("DECOR RECx={}, RECy={}, ScX={}, ScY={}, nbFrame={}", texture.getRecX(), texture.getRecY(), texture.getScX(), texture.getScY(), texture.getNbFrame());
    }

    Logger::getInstance()->info("PRINT LEVELS TEXTURES");
    for (const auto& [id, texture] : _levelTextures) {
        Logger::getInstance()->info("name id {}", id);
        Logger::getInstance()->info("LEVEL RECx={}, RECy={}, ScX={}, ScY={}, nbFrame={}", texture.getRecX(), texture.getRecY(), texture.getScX(), texture.getScY(), texture.getNbFrame());
    }
}

const std::unordered_map<std::string, Texture>& AssetManager::getPlayerTextures() const 
{
    return _playerTextures;
}

const std::unordered_map<std::string, Texture>& AssetManager::getEnemyTextures() const 
{
    return _enemyTextures;
}

const std::unordered_map<std::string, Texture>& AssetManager::getShootTextures() const 
{
    return _shootTextures;
}

const std::unordered_map<std::string, sf::Texture>& AssetManager::getMenuTexture() const 
{
    return _menuTexture;
}

const std::unordered_map<std::string, sf::Texture>& AssetManager::getBackgroundTextures() const 
{
    return _backgroundTextures;
}

const std::unordered_map<std::string, Texture>& AssetManager::getDecorTextures() const 
{
    return _decorTextures;
}

const std::unordered_map<std::string, Texture>& AssetManager::getLevelTextures() const 
{
    return _levelTextures;
}


const sf::Font& AssetManager::getFont() const 
{
    return _font;
}

const std::vector<std::string>& AssetManager::getTextOptions() const 
{
    return _menuOptions;
}

const sf::Font& AssetManager:: getSubtitleFont() const
{
    return _subtitleFont;
    
}
