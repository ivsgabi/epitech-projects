/*
** EPITECH PROJECT, 2024
** BackgroundSystem
** File description:
** BackgroundSystem
*/

#include <stdexcept>
#include "Renderer/BackgroundSystem.hpp"

BackgroundSystem::BackgroundSystem(
    std::unordered_map<std::string, sf::Texture> backgroundTextures, 
    std::unordered_map<std::string, Texture> decorTextures) 
    : _backgroundTextures(std::move(backgroundTextures)),
     _decorTextures(std::move(decorTextures)) 
{
    _bgSprite1.setPosition(0, 0);
    _bgSprite2.setPosition(_screenWidth, 0);
    _decorsSprite1.setPosition(0, 0);
    _decorsSprite2.setPosition(_screenWidth, 0);
};

void BackgroundSystem::init(const std::string& background, const std::string& decor)
{
    if (_backgroundTextures.find(background) != _backgroundTextures.end()) {
        _bgSprite1.setTexture(_backgroundTextures[background]);
        _bgSprite2.setTexture(_backgroundTextures[background]);
        // _bgSprite1.setPosition(0, 0);
        // _bgSprite2.setPosition(_screenWidth, 0);
    }
    if (_decorTextures.find(decor)  != _decorTextures.end()) {
        _decorsSprite1.setTexture(_decorTextures[decor].getTexture());
        _decorsSprite2.setTexture(_decorTextures[decor].getTexture());
        
        _decorsSprite1.setScale(_decorTextures[decor].getScX(), _decorTextures[decor].getScY());
        _decorsSprite2.setScale(_decorTextures[decor].getScX(), _decorTextures[decor].getScY());

        // _decorsSprite1.setPosition(0, 0);
        // _decorsSprite2.setPosition(_screenWidth, 0);
    }
}

void BackgroundSystem::renderBackground(sf::RenderWindow& window)
{
    window.draw(_bgSprite1);
    window.draw(_bgSprite2);
}

void BackgroundSystem::renderDecor(sf::RenderWindow& window)
{
    window.draw(_decorsSprite1);
    window.draw(_decorsSprite2);
}


void BackgroundSystem::update()
{
    _bgSprite1.move(_bgSpeed, 0);
    _bgSprite2.move(_bgSpeed, 0);

    if (_bgSprite1.getPosition().x <= -_screenWidth) {
        _bgSprite1.setPosition(_screenWidth, 0);
    }
    if (_bgSprite2.getPosition().x <= -_screenWidth) {
        _bgSprite2.setPosition(_screenWidth, 0);
    }
    _decorsSprite1.move(_decorsSpeed, 0);
    _decorsSprite2.move(_decorsSpeed, 0);

    if (_decorsSprite1.getPosition().x <= -_screenWidth) {
        _decorsSprite1.setPosition(_screenWidth, 0);
    }
    if (_decorsSprite2.getPosition().x <= -_screenWidth) {
        _decorsSprite2.setPosition(_screenWidth, 0);
    }
}
