/*
** EPITECH PROJECT, 2024
** MenuSystem
** File description:
** MenuSystem
*/

#ifndef MENUSYSTEM_HPP_
#define MENUSYSTEM_HPP_

#include <SFML/Graphics.hpp>
#include <vector>
#include <string>
#include <stdexcept>
#include <stack>
#include "State.hpp"

class MenuSystem {
    public:
        MenuSystem(const sf::Texture& bg, const sf::Texture& logo, const sf::Font& font, const std::vector<std::string>& options, bool is_button);
        ~MenuSystem() = default;

        void render(sf::RenderWindow& window);
        void navigate(int direction, bool horizontal);
        void select(std::stack<GameStateRendering>& stateStack);
        void handleInput(const sf::Event& event, std::stack<GameStateRendering>& stateStack);

    private:
        void updateArrowPosition();

        sf::Text _backButton;
        sf::Text _nextButton;
        sf::RectangleShape _backButtonBorder;
        sf::RectangleShape _nextButtonBorder;

        sf::Sprite _background;
        sf::Sprite _logo;
    
        sf::Font _font;
        std::vector<std::string> _menuOptions;
        std::vector<sf::Text> _menuTexts;
        
        sf::Text _EnterPS;
        sf::ConvexShape _arrow;
        
        size_t _currentSelection = 0;
        bool _horizontalMode = false; 
        bool _is_button;
};

#endif /* !MENUSYSTEM_HPP_ */
