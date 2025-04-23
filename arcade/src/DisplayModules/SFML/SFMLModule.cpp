/*
** EPITECH PROJECT, 2024
** SFMLModule
** File description:
** Arcade
*/

#include "DisplayModules/SFML/SFMLModule.hpp"

#include <iostream>

extern "C"
{
    SFMLModule *entry_point()
    {
        return new SFMLModule();
    }
}

SFMLModule::SFMLModule() {}

SFMLModule::~SFMLModule()
{
    std::cout << "SFML Unloading" << std::endl;
    // this->destroyRessources();
}

void SFMLModule::initDisplay(std::map<std::size_t, std::shared_ptr<Entity>> entities)
{
    this->_window = std::unique_ptr<sf::RenderWindow>(
        new sf::RenderWindow(sf::VideoMode(HEIGHT, WIDTH), "Arcade",
        sf::Style::Default | sf::Style::Resize));
    this->_window->setFramerateLimit(60);
    if (!this->_font.loadFromFile("./font/arial.ttf")) {
        throw Exceptions::DisplayModule::FontNotFound();
    }
    std::shared_ptr<Entity> snake = entities[1];
    if (snake->getNameType() == SPRITE) {
        if (!_snakeTexture.loadFromFile(snake->getTexture().c_str()))
            throw Exceptions::DisplayModule::FontNotFound();
    }
    std::shared_ptr<Entity> food = entities[2];
    if (food->getNameType() == SPRITE) {
        if (!_foodTexture.loadFromFile(food->getTexture().c_str()))
            throw Exceptions::DisplayModule::FontNotFound();
    }
    std::shared_ptr<Entity> wall = entities[3];
    if (wall->getNameType() == SPRITE) {
        if (!_wallTexture.loadFromFile(wall->getTexture().c_str()))
            throw Exceptions::DisplayModule::FontNotFound();
    }
    std::shared_ptr<Entity> empty = entities[4];
    if (empty->getNameType() == SPRITE) {
        if (!_emptyTexture.loadFromFile(empty->getTexture().c_str()))
            throw Exceptions::DisplayModule::FontNotFound();
    }

    this->_colors[ColorType::WHITE] = sf::Color::White;
    this->_colors[ColorType::RED] = sf::Color::Red;
    this->_colors[ColorType::PINK] = sf::Color(255, 192, 203);
    this->_colors[ColorType::YELLOW] = sf::Color::Yellow;
    this->_colors[ColorType::BLUE] = sf::Color::Blue;
    this->_colors[ColorType::GREEN] = sf::Color::Green;
    this->_colors[ColorType::ORANGE] = sf::Color(255, 87, 51);
    this->_colors[ColorType::BLACK] = sf::Color::Black;
    std::cout << "everything is init" << std::endl;
}

void SFMLModule::destroyRessources()
{}

void SFMLModule::clearScreen()
{
    this->_window->clear();
}


void SFMLModule::drawEntities(std::map<std::size_t, std::shared_ptr<Entity>> entities)
{
    for (const auto &[index, entity] : entities) {
        if (entity->getNameType() == NameType::TEXT) {
            sf::Text text;
            text.setFont(this->_font);
            text.setString(entity->getText());
            text.setCharacterSize(entity->getDimensions().first);
            text.setFillColor(this->_colors[entity->getColor()]);
            text.move(entity->getPosition().first * OFFSET,
            entity->getPosition().second * OFFSET);
            this->_window->draw(text);
        }
        if (entity->getNameType() == NameType::MAP) {
            std::vector<std::string> map = entity->getMap();
            std::shared_ptr<Entity> snake = entities[1];
            std::shared_ptr<Entity> food = entities[2];
            std::shared_ptr<Entity> wall = entities[3];
            std::shared_ptr<Entity> empty = entities[4];

            sf::Vector2u windowSize = _window->getSize();
            float squareSize = 40.0f;
            long unsigned int mapHeight = map.size();
            long unsigned int mapWidth = 0;
            long unsigned int x = 0;
            long unsigned int y = 0;

            for (const auto& row : map) {
                if (row.length() > mapWidth)
                    mapWidth = row.length();
            }
            float startX = (windowSize.x - mapWidth * squareSize) / 2.0f;
            float startY = (windowSize.y - mapHeight * squareSize) / 2.0f;

            for (y = 0; y < mapHeight; y++) {
                for (x = 0; x < map[y].length(); x++) {
                    sf::RectangleShape posRect(sf::Vector2f(squareSize, squareSize));
                    posRect.setPosition(startX + x * squareSize, startY + y * squareSize);

                    if (map[y][x] == '#') {
                        posRect.setTexture(&_wallTexture);
                        _window->draw(posRect);
                    } 
                    if (map[y][x] == 'o') {
                        posRect.setTexture(&_foodTexture);
                        posRect.setScale(sf::Vector2f(1, 1));
                        _window->draw(posRect);
                    }
                    if (map[y][x] == 'S') {
                        posRect.setTexture(&_snakeTexture);
                        _window->draw(posRect);
                    }
                    if (map[y][x] == ' ') {
                        posRect.setTexture(&_emptyTexture);
                        _window->draw(posRect);
                    }
                }
            }
        }
    }
    _window->display();
}

void SFMLModule::handleEvents(const std::string &crtGameLib)
{
    this->_event = Event();

    while (this->_window->pollEvent(this->_eventSFML)) {
        this->handleWindowEvents();
        this->handleKeyboardEvents();
    }
}

void SFMLModule::handleWindowEvents()
{
    WindowEvent windowEvent;

    if (this->_eventSFML.type == sf::Event::Closed) {
        this->_event.setEventType(WINDOW_E);
        windowEvent.setEvent(CLOSED);
        this->_event.setWindowEvent(windowEvent);
    }
}

void SFMLModule::checkKeyPressed(KeyboardEvent &keyboardEvent)
{
    if (this->_eventSFML.key.code == sf::Keyboard::Space) {
        keyboardEvent.setInput(NEXT_GRAPHICAL);
    }
    if (this->_eventSFML.key.code == sf::Keyboard::Enter) {
        keyboardEvent.setInput(NEXT_GAME);
    }
    if (this->_eventSFML.key.code == sf::Keyboard::Left) {
        keyboardEvent.setInput(LEFT);
    }
    if (this->_eventSFML.key.code == sf::Keyboard::Right) {
        keyboardEvent.setInput(RIGHT);
    }
    if (this->_eventSFML.key.code == sf::Keyboard::Up) {
        keyboardEvent.setInput(UP);
    }
    if (this->_eventSFML.key.code == sf::Keyboard::Down) {
        keyboardEvent.setInput(DOWN);
    }
    if (this->_eventSFML.key.code == sf::Keyboard::Q) {
        keyboardEvent.setInput(GO_BACK_MENU);
    }
    if (this->_eventSFML.key.code == sf::Keyboard::Escape) {
        keyboardEvent.setInput(EXIT);
    }
    if (this->_alphabetLetters.find(this->_eventSFML.key.code)
        != this->_alphabetLetters.end()) {
        keyboardEvent.setInput(this->_alphabetLetters.at(this->_eventSFML.key.code));
    }
}

void SFMLModule::handleKeyboardEvents()
{
    KeyboardEvent keyboardEvent;

    if (this->_eventSFML.type == sf::Event::KeyPressed) {
        this->_event.setEventType(KEYBOARD);
        this->checkKeyPressed(keyboardEvent);
        this->_event.setKeyboardEvent(keyboardEvent);
    }
}

Event &SFMLModule::getEvent()
{
    return this->_event;
}