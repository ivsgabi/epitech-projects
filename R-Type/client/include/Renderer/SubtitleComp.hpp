/*
** EPITECH PROJECT, 2025
** SubtitleComp.hpp
** File description:
** SubtitleComp
*/

#include <SFML/Graphics.hpp>
#include <unordered_map>
#include <string>
#include <iostream>
#include "GameEvent.hpp"

class SubtitleComp {
    public:
        SubtitleComp() = default;
        SubtitleComp(const sf::Font& font);
        ~SubtitleComp() = default;

        void addSubtitle(SubtitleEvent event, const std::string& text);
        void displaySubtitle(SubtitleEvent event, sf::RenderWindow& window);

    private:
        sf::Font _font;
        std::unordered_map<SubtitleEvent, std::pair<sf::RectangleShape, sf::Text>> _subtitlesBank;
};
