/*
** EPITECH PROJECT, 2025
** BasicComp.cpp
** File description:
** BasicComp
*/

#include "Renderer/BasicComp.hpp"

BasicComp::BasicComp(const sf::Font& defaultFont) : _defaultFont(defaultFont) {}

sf::Text BasicComp::createCustomText(const std::string& text, unsigned int characterSize, sf::Color color, sf::Vector2f position, sf::Text::Style style)
{
    sf::Text sfText;
    sfText.setFont(_defaultFont);
    sfText.setString(text);
    sfText.setCharacterSize(characterSize);
    sfText.setFillColor(color);
    sfText.setStyle(style);
    sfText.setPosition(position);
    return sfText;
}

sf::RectangleShape BasicComp::createRectangle(sf::Vector2f size, sf::Color fillColor, sf::Color outlineColor, float outlineThickness, sf::Vector2f position)
{
    sf::RectangleShape rectangle;
    rectangle.setSize(size);
    rectangle.setFillColor(fillColor);
    rectangle.setOutlineColor(outlineColor);
    rectangle.setOutlineThickness(outlineThickness);
    rectangle.setPosition(position);
    return rectangle;
}

sf::RectangleShape BasicComp::createBorderedRectangleForText(const sf::Text& text, float paddingX, float paddingY, sf::Color outlineColor, float outlineThickness)
{
    sf::FloatRect textBounds = text.getGlobalBounds();
    sf::RectangleShape border;
    border.setSize({textBounds.width + paddingX * 2.0f, textBounds.height + paddingY * 2.0f});
    border.setPosition(sf::Vector2f(text.getPosition().x - 10, text.getPosition().y - 10));
    border.setFillColor(sf::Color::Transparent);
    border.setOutlineColor(outlineColor);
    border.setOutlineThickness(outlineThickness);
    return border;
}

sf::ConvexShape BasicComp::createArrow(sf::Vector2f position, sf::Vector2f size, sf::Color color)
{
    sf::ConvexShape arrow;
    arrow.setPointCount(3);
    arrow.setPoint(0, sf::Vector2f(0, 30));
    arrow.setPoint(1, sf::Vector2f(-20, 0));
    arrow.setPoint(2, sf::Vector2f(20, 0));
    arrow.setFillColor(color);
    arrow.setPosition(position);
    return arrow;
}

sf::Sprite BasicComp::createSprite(const sf::Texture& texture, sf::Vector2f position, sf::Vector2f scale, sf::Vector2f origin)
{
    sf::Sprite sprite;
    sprite.setTexture(texture);
    sprite.setScale(scale);
    sprite.setOrigin(origin);
    sprite.setPosition(position);
    return sprite;
}

sf::RectangleShape BasicComp::createBlurOverlay(sf::Vector2f size, sf::Color color)
{
    sf::RectangleShape blurOverlay;
    blurOverlay.setSize(size);
    blurOverlay.setFillColor(color);
    return blurOverlay;
}


void BasicComp::centerTextHorizontally(sf::Text& text, float windowWidth)
{
    sf::FloatRect bounds = text.getLocalBounds();
    text.setPosition((windowWidth - bounds.width) / 2.0f, text.getPosition().y);
}
