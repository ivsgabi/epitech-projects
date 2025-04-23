/*
** EPITECH PROJECT, 2024
** SFMLModule
** File description:
** Arcade
*/

#ifndef SFML_MODULE_HPP_
#define SFML_MODULE_HPP_
#include <SFML/Graphics.hpp>
#include <unordered_map>
#include "DisplayModules/ADisplayModule.hpp"
#define HEIGHT 800
#define WIDTH 600
#define OFFSET 12

class SFMLModule : public ADisplayModule {
    public:
        SFMLModule();
        ~SFMLModule();
        void initDisplay(std::map<std::size_t, std::shared_ptr<Entity>> entities) final;
        void destroyRessources() final;
        void clearScreen() final;
        void drawEntities(std::map<std::size_t, std::shared_ptr<Entity>> entities) final;
        void handleEvents(const std::string &crtGameLib) final;
        Event &getEvent() final;

    private:
        std::unique_ptr<sf::RenderWindow> _window;
        std::unordered_map<ColorType, sf::Color> _colors;
        sf::Event _eventSFML;
        Event _event;
        sf::Font _font;
        std::string _textureStr;
        sf::Texture _snakeTexture;
        sf::Texture _foodTexture; 
        sf::Texture _wallTexture;
        sf::Texture _emptyTexture;
        void handleWindowEvents();
        void handleKeyboardEvents();
        void checkKeyPressed(KeyboardEvent &keyboardEvent);
        const std::unordered_map<sf::Keyboard::Key, KeyboardEventType> _alphabetLetters =
        {
            { sf::Keyboard::A, KeyboardEventType::A },
            { sf::Keyboard::B, KeyboardEventType::B },
            { sf::Keyboard::C, KeyboardEventType::C },
            { sf::Keyboard::D, KeyboardEventType::D },
            { sf::Keyboard::E, KeyboardEventType::E },
            { sf::Keyboard::F, KeyboardEventType::F },
            { sf::Keyboard::G, KeyboardEventType::G },
            { sf::Keyboard::H, KeyboardEventType::H },
            { sf::Keyboard::I, KeyboardEventType::I },
            { sf::Keyboard::J, KeyboardEventType::J },
            { sf::Keyboard::K, KeyboardEventType::K },
            { sf::Keyboard::L, KeyboardEventType::L },
            { sf::Keyboard::M, KeyboardEventType::M },
            { sf::Keyboard::N, KeyboardEventType::N },
            { sf::Keyboard::O, KeyboardEventType::O },
            { sf::Keyboard::P, KeyboardEventType::P },
            { sf::Keyboard::Q, KeyboardEventType::Q },
            { sf::Keyboard::R, KeyboardEventType::R },
            { sf::Keyboard::S, KeyboardEventType::S },
            { sf::Keyboard::T, KeyboardEventType::T },
            { sf::Keyboard::U, KeyboardEventType::U },
            { sf::Keyboard::V, KeyboardEventType::V },
            { sf::Keyboard::W, KeyboardEventType::W },
            { sf::Keyboard::X, KeyboardEventType::X },
            { sf::Keyboard::Y, KeyboardEventType::Y },
            { sf::Keyboard::Z, KeyboardEventType::Z },
        };
};

#endif /* !SFML_MODULE_HPP_ */
