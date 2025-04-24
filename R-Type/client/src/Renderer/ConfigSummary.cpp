/*
** EPITECH PROJECT, 2024
** ConfigSummary.cpp
** File description:
** ConfigSummary
*/

#include "Renderer/ConfigSummary.hpp"
#include "Renderer/BasicComp.hpp"
#include "../../../networking/include/Logger.hpp"

ConfigSummary:: ConfigSummary(const sf::Font& font, 
    const sf::Texture& bg, 
    const std::unordered_map<std::string, Texture>& textures)
 : _font(font), _bgTexture(bg), _textures(textures)
{
    init();
}

void ConfigSummary::init()
{
    BasicComp basicComp(_font);

    _bgSprite.setTexture(_bgTexture);

    _titleText = basicComp.createCustomText(
        "ROOM", 50, sf::Color::White, 
        {980 - _titleText.getLocalBounds().width / 2, 50}
    );
    basicComp.centerTextHorizontally(_titleText, 1920);


    _confirmButton = basicComp.createCustomText(
        "Confirm", 40, sf::Color::White, 
        {950 - _confirmButton.getLocalBounds().width / 2, 600}
    );
    basicComp.centerTextHorizontally(_confirmButton, 1920);
    _confirmBorder = basicComp.createBorderedRectangleForText(_confirmButton);

    _backButton = basicComp.createCustomText(
        "Back", 40, sf::Color::White, 
        {950 - _backButton.getLocalBounds().width / 2, 700}
    );
    basicComp.centerTextHorizontally(_backButton, 1920);
    _backBorder = basicComp.createBorderedRectangleForText(_backButton);

    updateSelection(true);
}

void ConfigSummary::setConfig(const std::string& path)
{
    sf::Sprite sprite;
    if (_textures.find(path) != _textures.end()) {
        sprite.setTexture(_textures.at(path).getTexture());
        sprite.setTextureRect(sf::IntRect(
                0,
                0,
                _textures.at(path).getRecX(),
                _textures.at(path).getRecY()
        ));
    }
    _configSprites.push_back(sprite);

    const float maxThumbnailWidth = 300.0f; 
    const float maxThumbnailHeight = 200.0f;
    const float centerX = 950.0f;
    const float centerY = 450.0f;

    for (size_t i = 0; i < _configSprites.size(); ++i) {
        _configSprites[i].setScale(6, 6);
        sf::FloatRect bounds = _configSprites[i].getLocalBounds();

        float scaleX = maxThumbnailWidth / bounds.width;
        float scaleY = maxThumbnailHeight / bounds.height;
        _configSprites[i].setOrigin(bounds.width / 2.0f, bounds.height / 2.0f);
        _configSprites[i].setPosition(centerX, centerY);
    }
}

void ConfigSummary::render(sf::RenderWindow& window, std::unordered_map<int, std::shared_ptr<Entity>> entities, int lobby)
{
    window.draw(_bgSprite);
    window.draw(_titleText);

    std::string nbClientContent = "0 players";

    if (entities.count(206)) {
        nbClientContent = std::to_string(static_cast<int>(entities[206]->getX())) + "players";
    }
    sf::Text nbClientText;
    nbClientText.setFont(_font);
    nbClientText.setString(nbClientContent);
    nbClientText.setCharacterSize(30);
    nbClientText.setFillColor(sf::Color::Red);
    nbClientText.setPosition(
        960 - nbClientText.getLocalBounds().width / 2,
        _titleText.getPosition().y + _titleText.getLocalBounds().height + 40
    );
    window.draw(nbClientText);
    for (auto& sprite : _configSprites) {
        sf::RectangleShape border;
        sf::FloatRect spriteBounds = sprite.getGlobalBounds();
        border.setSize(sf::Vector2f(spriteBounds.width + 10.0f, spriteBounds.height + 10.0f));
        border.setOrigin(border.getSize().x / 2.0f, border.getSize().y / 2.0f);
        border.setPosition(sprite.getPosition());
        border.setFillColor(sf::Color::Transparent);
        border.setOutlineColor(sf::Color(255, 255, 255, 128));
        border.setOutlineThickness(3);
        window.draw(border);
        window.draw(sprite);
    }
    window.draw(_confirmBorder);
    window.draw(_confirmButton);
    if (lobby ==1 ) {
        std::string loadingContent = "Waiting the other players";
        sf::Text loadingText;
        loadingText.setFont(_font);
        loadingText.setString(loadingContent);
        loadingText.setCharacterSize(30);
        loadingText.setFillColor(sf::Color::Yellow);
        loadingText.setPosition(
            960 - loadingText.getLocalBounds().width / 2,
            _titleText.getPosition().y + _titleText.getLocalBounds().height + 80
        );
        window.draw(loadingText);
    }
    window.draw(_backBorder);
    window.draw(_backButton);
}

void ConfigSummary::handleInput(const sf::Event& event, bool& confirmed, bool& back)
{
    if (event.type == sf::Event::KeyPressed) {
        if (event.key.code == sf::Keyboard::Up || event.key.code == sf::Keyboard::Down) {
            _confirmSelected = !_confirmSelected;
            updateSelection(_confirmSelected);
        } else if (event.key.code == sf::Keyboard::Enter) {
            if (_confirmSelected) {
                confirmed = true;
            } else {
                back = true;
            }
        }
    }
}

void ConfigSummary::updateSelection(bool confirm)
{
    if (confirm) {
        _confirmBorder.setOutlineColor(sf::Color::Yellow);
        _backBorder.setOutlineColor(sf::Color::White);
    } else {
        _confirmBorder.setOutlineColor(sf::Color::White);
        _backBorder.setOutlineColor(sf::Color::Yellow);
    }
}
