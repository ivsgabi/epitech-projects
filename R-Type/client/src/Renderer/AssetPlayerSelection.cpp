/*
** EPITECH PROJECT, 2024
** AssetPlayerSelection.cpp
** File description:
** AssetPlayerSelection
*/
#include "Renderer/AssetPlayerSelection.hpp"

AssetPlayerSelection::AssetPlayerSelection(const sf::Font& font, const sf::Texture& background, const std::unordered_map<std::string, Texture>& assetsSelection)
    : _currentSelection(0), _confirmed(false), _assetsTextures(assetsSelection)
{
    BasicComp basicComp(font);
    _bg.setTexture(background);

    _titleText = basicComp.createCustomText(
        "ASSETS PLAYERS", 50, sf::Color::White, {0, 150}, sf::Text::Bold
    );
    basicComp.centerTextHorizontally(_titleText, 1920);

    _instructionText = basicComp.createCustomText(
        "Use ARROWS to navigate, ENTER to select", 
        20, sf::Color(200, 200, 200), {0, 720}
    );
    basicComp.centerTextHorizontally(_instructionText, 1920);

    _arrow = basicComp.createArrow(
        {0, 0}, {40, 80}, sf::Color::Yellow
    );
    initObjectsSelection(basicComp);
}

AssetPlayerSelection::~AssetPlayerSelection() {}

void AssetPlayerSelection::initObjectsSelection(BasicComp& basicComp)
{
    const float maxThumbnailWidth = 200.0f;
    const float maxThumbnailHeight = 150.0f;
    const float gapX = 50.0f;
    const float centerY = 500.0f;
    const float windowWidth = 1920.0f;

    size_t spriteCount = _assetsTextures.size();
    if (spriteCount == 0) {
        return;
    }

    float totalWidth = spriteCount * maxThumbnailWidth + (spriteCount - 1) * gapX;
    float startX = (windowWidth - totalWidth) / 2.0f;

    for (const auto& [path, texture] : _assetsTextures) {
        sf::Sprite sprite;
        sprite.setTexture(texture.getTexture());

        sprite.setTextureRect(sf::IntRect(0, 0, texture.getRecX(), texture.getRecY()));

        sf::FloatRect originalBounds = sprite.getLocalBounds();
        float scaleX = maxThumbnailWidth / originalBounds.width;
        float scaleY = maxThumbnailHeight / originalBounds.height;
        float finalScale = std::min(scaleX, scaleY);
        sprite.setScale(finalScale, finalScale);
        sprite.setOrigin(originalBounds.width / 2, originalBounds.height / 2);

        sprite.setPosition(startX + maxThumbnailWidth / 2, centerY);
        startX += maxThumbnailWidth + gapX;

        sf::RectangleShape border = basicComp.createRectangle(
            sf::Vector2f(sprite.getGlobalBounds().width + 10.0f, sprite.getGlobalBounds().height + 10.0f),
            sf::Color::Transparent, sf::Color(255, 255, 255, 128), 5.0f
        );
        border.setOrigin(border.getSize().x / 2, border.getSize().y / 2);
        border.setPosition(sprite.getPosition());

        _assetsSprites.push_back(sprite);
        _assetsBorders.push_back(border);
    }

    updateSelectionDisplay();
}

void AssetPlayerSelection::render(sf::RenderWindow& window)
{
    window.draw(_bg);

    window.draw(_titleText);

    for (size_t i = 0; i < _assetsSprites.size(); ++i) {
        if (i == _currentSelection) {
            _assetsBorders[i].setOutlineColor(sf::Color::Yellow);
            _assetsSprites[i].setColor(sf::Color::White);
        } else {
            _assetsBorders[i].setOutlineColor(sf::Color(255, 255, 255, 128));
            _assetsSprites[i].setColor(sf::Color(200, 200, 200));
        }

        window.draw(_assetsBorders[i]);
        window.draw(_assetsSprites[i]);
    }

    window.draw(_arrow);
    window.draw(_instructionText);
}

void AssetPlayerSelection::handleInput(const sf::Event& event)
{
    if (event.type == sf::Event::KeyPressed) {
        if (event.key.code == sf::Keyboard::Left) {
            _currentSelection = (_currentSelection == 0) ? _assetsSprites.size() - 1 : _currentSelection - 1;
        } else if (event.key.code == sf::Keyboard::Right) {
            _currentSelection = (_currentSelection + 1) % _assetsSprites.size();
        } else if (event.key.code == sf::Keyboard::Enter) {
            _confirmed = true;
        }
    }
    updateSelectionDisplay();
}

void AssetPlayerSelection::updateSelectionDisplay()
{
    if (_assetsSprites.empty()) {
        return;
    }

    sf::Vector2f selectedSpritePos = _assetsSprites[_currentSelection].getPosition();
    _arrow.setPosition(selectedSpritePos.x, selectedSpritePos.y - 210);
}

const Texture& AssetPlayerSelection::getSelectedAsset() const
{
    auto it = _assetsTextures.begin();
    std::advance(it, _currentSelection);
    return it->second;
}

bool AssetPlayerSelection::getConfirmed()
{
    return _confirmed;
}

void AssetPlayerSelection::resetConfirmed()
{
    _confirmed = false;
}
