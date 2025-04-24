/*
** EPITECH PROJECT, 2025
** SubtitleComp.cpp
** File description:
** SubtitleComp
*/
#include "Renderer/SubtitleComp.hpp"

SubtitleComp::SubtitleComp(const sf::Font& font) : _font(font) { }

void SubtitleComp::addSubtitle(SubtitleEvent event, const std::string& text) 
{
    sf::Text subtitleText;
    subtitleText.setFont(_font);
    subtitleText.setString(text);
    subtitleText.setCharacterSize(40);
    subtitleText.setFillColor(sf::Color::White);

    sf::FloatRect textBounds = subtitleText.getLocalBounds();
    float padding = 20.0f;
    sf::RectangleShape subtitleBox;
    subtitleBox.setSize(sf::Vector2f(textBounds.width + 2 * padding, textBounds.height + 2 * padding));
    subtitleBox.setFillColor(sf::Color::Black);
    subtitleBox.setOutlineColor(sf::Color::Black);
    subtitleBox.setOutlineThickness(2);

    _subtitlesBank[event] = std::make_pair(subtitleBox, subtitleText);
}

void SubtitleComp::displaySubtitle(SubtitleEvent event, sf::RenderWindow& window)
{
    if (_subtitlesBank.find(event) != _subtitlesBank.end()) {
        auto& [box, text] = _subtitlesBank[event];

        float windowWidth = window.getSize().x;
        float windowHeight = window.getSize().y;

        sf::Vector2f boxSize = box.getSize();
        float x = (windowWidth - boxSize.x) / 2.0f;
        float y = windowHeight - boxSize.y - 80.0f;

        box.setPosition(x, y);

        sf::FloatRect textBounds = text.getLocalBounds();
        text.setPosition(
            x + (boxSize.x - textBounds.width) / 2.0f - textBounds.left, 
            y + (boxSize.y - textBounds.height) / 2.0f - textBounds.top
        );

        window.draw(box);
        window.draw(text);
    }
}
