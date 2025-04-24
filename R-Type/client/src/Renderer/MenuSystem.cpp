/*
** EPITECH PROJECT, 2024
** MenuSystem.cpp
** File description:
** MenuSystem
*/
 
#include "Renderer/MenuSystem.hpp"
#include <Renderer/BasicComp.hpp>

MenuSystem::MenuSystem(const sf::Texture& bg, const sf::Texture& logo, const sf::Font& font, const std::vector<std::string>& options, bool is_button) :  
_menuOptions(options), _is_button(is_button), _font(font)
{
    BasicComp basicComp(font);
    _background.setTexture(bg);
    _logo = basicComp.createSprite(logo, sf::Vector2f{155, -40}, sf::Vector2f{2.5f, 2.5f}, sf::Vector2f{0, 0});
    
    float startY = 450;
    float lineSpacing = 70;
    for (size_t i = 0; i < _menuOptions.size(); ++i) {
        sf::Text text = basicComp.createCustomText(
            _menuOptions[i], 40, sf::Color::White, 
            {960, startY + i * lineSpacing}, sf::Text::Regular
        );

        text.setPosition(960 - text.getLocalBounds().width / 2, text.getPosition().y);
        _menuTexts.push_back(text);
    }

    if (_is_button) {
        _backButton = basicComp.createCustomText("Back", 40, sf::Color::White);
        _backButton.setPosition(200 - _backButton.getLocalBounds().width / 2, 500);

        _nextButton = basicComp.createCustomText("Next", 40, sf::Color::White);
        _nextButton.setPosition(1720 - _nextButton.getLocalBounds().width / 2, 500);

        _backButtonBorder = basicComp.createBorderedRectangleForText(_backButton, 15, 15, sf::Color::White, 2);
        _nextButtonBorder = basicComp.createBorderedRectangleForText(_nextButton, 15, 15, sf::Color::White, 2);
    }

    _EnterPS = basicComp.createCustomText(
        "Press ENTER to select", 
        20, sf::Color(200, 200, 200), {0, 730}
    );
    _EnterPS.setPosition(960 - _EnterPS.getLocalBounds().width / 2, 730);

    _arrow = basicComp.createArrow({0, 0}, {30, 20}, sf::Color::Yellow);

    updateArrowPosition();
}

// void MenuSystem::init()
// {
//     _logo.setScale(2.5f, 2.5f);
//     _logo.setPosition(155, -40);

//     float startY = 450;
//     float lineSpacing = 70;
//     for (size_t i = 0; i < _menuOptions.size(); ++i) {
//         sf::Text text(_menuOptions[i], _font, 40);
//         text.setFillColor(sf::Color::White);
//         text.setPosition(960 - text.getLocalBounds().width / 2, startY + i * lineSpacing);
//         _menuTexts.push_back(text);
//     }
    
//     if (_is_button) {
//         _backButton.setFont(_font);
//         _backButton.setString("Back");
//         _backButton.setCharacterSize(40);
//         _backButton.setFillColor(sf::Color::White);
//         _backButton.setPosition(200 - _backButton.getLocalBounds().width / 2, 500);
//         _nextButton.setFont(_font);
//         _nextButton.setString("Next");
//         _nextButton.setCharacterSize(40);
//         _nextButton.setFillColor(sf::Color::White);
//         _nextButton.setPosition(1720 - _nextButton.getLocalBounds().width / 2, 500);

//         _backButtonBorder.setSize(sf::Vector2f(_backButton.getLocalBounds().width + 30, _backButton.getLocalBounds().height + 30));
//         _backButtonBorder.setPosition(_backButton.getPosition().x - 10, _backButton.getPosition().y - 10);
//         _backButtonBorder.setFillColor(sf::Color::Transparent);
//         _backButtonBorder.setOutlineColor(sf::Color::White);
//         _backButtonBorder.setOutlineThickness(2);
//         _nextButtonBorder.setSize(sf::Vector2f(_nextButton.getLocalBounds().width + 30, _nextButton.getLocalBounds().height + 30));
//         _nextButtonBorder.setPosition(_nextButton.getPosition().x - 10, _nextButton.getPosition().y - 10);
//         _nextButtonBorder.setFillColor(sf::Color::Transparent);
//         _nextButtonBorder.setOutlineColor(sf::Color::White);
//         _nextButtonBorder.setOutlineThickness(2);
//     }
//     _EnterPS.setString("Press ENTER to select");
//     _EnterPS.setFont(_font);
//     _EnterPS.setCharacterSize(20);
//     _EnterPS.setFillColor(sf::Color(200, 200, 200));
//     _EnterPS.setPosition(960 - _EnterPS.getLocalBounds().width / 2, 730);

//     _arrow.setPointCount(3);
//     _arrow.setPoint(0, sf::Vector2f(0, 20));
//     _arrow.setPoint(1, sf::Vector2f(-30, 10));
//     _arrow.setPoint(2, sf::Vector2f(0, 0));
//     _arrow.setFillColor(sf::Color::Yellow);
//     updateArrowPosition();
// }

void MenuSystem::render(sf::RenderWindow& window)
{
    window.draw(_background);
    window.draw(_logo);

    for (size_t i = 0; i < _menuTexts.size(); ++i) {
        if (i == _currentSelection) {
            _menuTexts[i].setFillColor(sf::Color::Yellow);
            _menuTexts[i].setScale(1.2f, 1.2f);
        } else {
            _menuTexts[i].setFillColor(sf::Color::White);
            _menuTexts[i].setScale(1.0f, 1.0f);
        }
        window.draw(_menuTexts[i]);
    }
    if (_is_button) {
        _backButtonBorder.setOutlineColor((_currentSelection == _menuOptions.size()) ? sf::Color::Yellow : sf::Color::White);
        _nextButtonBorder.setOutlineColor((_currentSelection == _menuOptions.size() + 1) ? sf::Color::Yellow : sf::Color::White);
        window.draw(_backButtonBorder);
        window.draw(_backButton);
        window.draw(_nextButtonBorder);
        window.draw(_nextButton);
    }

    window.draw(_arrow);
    window.draw(_EnterPS);
}

void MenuSystem::navigate(int direction, bool horizontal)
{
    int totalItems =  (_is_button) ? _menuOptions.size() + 2 : _menuOptions.size();
    if (_is_button && horizontal) {
        if (_currentSelection >= _menuOptions.size()) {
            _currentSelection = (_currentSelection == _menuOptions.size() + 1 && direction == -1)
                                    ? _menuOptions.size()
                                    : (_currentSelection == _menuOptions.size() && direction == 1)
                                          ? _menuOptions.size() + 1
                                          : _menuOptions.size();
        } else {
            _currentSelection = (direction == -1) ? _menuOptions.size() : _menuOptions.size() + 1;
        }
    } else {
        if (_currentSelection < _menuOptions.size()) {
            _currentSelection = (_currentSelection + direction + _menuOptions.size()) % _menuOptions.size();
        } else {
            _currentSelection = 0;
        }
    }
    updateArrowPosition();
}

void MenuSystem::select(std::stack<GameStateRendering>& stateStack)
{
    if (_is_button && _currentSelection == _menuOptions.size()) {
        if (!stateStack.empty()) stateStack.pop();
    } else if (_is_button && _currentSelection == _menuOptions.size() + 1) {
        stateStack.push(GameStateRendering::CONFIG_SUMMARY);
    } else {
        if (_menuOptions[_currentSelection] == "QUIT") {
            stateStack = std::stack<GameStateRendering>();
        } else if (_menuOptions[_currentSelection] == "START") {
            stateStack.push(GameStateRendering::MENU_OPT);
        } else if (_menuOptions[_currentSelection] == "HELP") {
            stateStack.push(GameStateRendering::HELP);
        } else if (_menuOptions[_currentSelection] == "ASSETS PLAYER") {
            stateStack.push(GameStateRendering::ASSET_PLAYER);
        } else if (_menuOptions[_currentSelection] == "LEVELS") {
            stateStack.push(GameStateRendering::LEVELS);
        }
    }
}

void MenuSystem::handleInput(const sf::Event& event, std::stack<GameStateRendering>& stateStack)
{
    if (event.type == sf::Event::KeyPressed) {
        if (event.key.code == sf::Keyboard::Up) {
            navigate(-1, false);
        } else if (event.key.code == sf::Keyboard::Down) {
            navigate(1, false);
        } else if (event.key.code == sf::Keyboard::Left) {
            navigate(-1, true);
        } else if (event.key.code == sf::Keyboard::Right) {
            navigate(1, true);
        } else if (event.key.code == sf::Keyboard::Enter) {
            select(stateStack);
        }
    }
}

void MenuSystem::updateArrowPosition()
{
    if (_currentSelection < _menuOptions.size()) {
        sf::FloatRect selectedBounds = _menuTexts[_currentSelection].getGlobalBounds();
        _arrow.setPosition(selectedBounds.left + selectedBounds.width + 150, selectedBounds.top + selectedBounds.height / 2 - 10);
    } else if (_currentSelection == _menuOptions.size()) {
        _arrow.setPosition(_backButton.getPosition().x + _backButton.getLocalBounds().width + 20, _backButton.getPosition().y + 10);
    } else if (_currentSelection == _menuOptions.size() + 1) {
        _arrow.setPosition(_nextButton.getPosition().x + _nextButton.getLocalBounds().width + 20, _nextButton.getPosition().y + 10);
    }
}