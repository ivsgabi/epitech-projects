/*
** EPITECH PROJECT, 2025
** BasicComp.hpp
** File description:
** BasicComp
*/

#ifndef BASICCOMP_HPP_
#define BASICCOMP_HPP_

#include <SFML/Graphics.hpp>

class BasicComp {
    public:
        BasicComp() = default;
        explicit BasicComp(const sf::Font& defaultFont);
        ~BasicComp() = default;

        sf::Text createCustomText(
            const std::string& text, 
            unsigned int characterSize = 30, 
            sf::Color color = sf::Color::White, 
            sf::Vector2f position = {0.f, 0.f}, 
            sf::Text::Style style = sf::Text::Regular
        );

        sf::RectangleShape createRectangle(
            sf::Vector2f size, 
            sf::Color fillColor = sf::Color::White, 
            sf::Color outlineColor = sf::Color::Transparent, 
            float outlineThickness = 0.f, 
            sf::Vector2f position = {0.f, 0.f}
        );

        sf::RectangleShape createBorderedRectangleForText(
            const sf::Text& text, 
            float paddingX = 15.f, 
            float paddingY = 10.f, 
            sf::Color outlineColor = sf::Color::White, 
            float outlineThickness = 2.f
        );

        sf::ConvexShape createArrow(
            sf::Vector2f position = {0.f, 0.f}, 
            sf::Vector2f size = {50.f, 100.f}, 
            sf::Color color = sf::Color::White
        );

        sf::Sprite createSprite(
            const sf::Texture& texture, 
            sf::Vector2f position = {0.f, 0.f}, 
            sf::Vector2f scale = {1.f, 1.f}, 
            sf::Vector2f origin = {0.f, 0.f}
        );

        sf::RectangleShape createBlurOverlay(
            sf::Vector2f size, 
            sf::Color color = sf::Color(0, 0, 0, 150)
        );
        
        void centerTextHorizontally(sf::Text& text, float windowWidth);

    private:
        const sf::Font& _defaultFont;
};

#endif /* !BASICCOMP_HPP_ */
