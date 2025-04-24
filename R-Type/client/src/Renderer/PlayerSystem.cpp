/*
** EPITECH PROJECT, 2024
** PlayerSystem.cpp
** File description:
** PlayerSystem
*/

#include <stdexcept>
#include "Renderer/DefaultValues.hpp"
#include "Renderer/PlayerSystem.hpp"
#include "../../../networking/include/Logger.hpp"

PlayerSystem::PlayerSystem(
    const std::unordered_map<std::string, Texture>& bulletTextures,
    const std::unordered_map<std::string, Texture>& playersTextures,
    std::stack<GameEvent>& eventStack,
    bool& isShootingGame
)
 : _playersTextures(playersTextures), _bulletTextures(bulletTextures), _eventStack(eventStack), _isShootingGame(isShootingGame)
{}

static std::string trimNulls(const std::string& str)
{
    size_t end = str.find_last_not_of('\0');
    return str.substr(0, end + 1); 
}

void PlayerSystem:: initBulletSprite(const std::string& path)
{
    if (_bulletTextures.find(path) != _bulletTextures.end()) {
        _bulletTexture = _bulletTextures.at(path);
        _bulletSprite.setTexture(_bulletTextures.at(path).getTexture());
        _bulletSprite.setTextureRect(sf::IntRect(
                0,
                0,
                _bulletTextures.at(path).getRecX(),
                _bulletTextures.at(path).getRecY()
            ));
        _bulletSprite.setScale(_bulletTextures.at(path).getScX(), _bulletTextures.at(path).getScY());
    }
}

void PlayerSystem::initPlayer(const std::string& path)
{
    if (_playersTextures.find(path) != _playersTextures.end()) {
        Logger::getInstance()->info("Texture trouvé init player path {}", path);
        _playerText = _playersTextures.at(path);
        _playerSprite.setTexture(_playersTextures.at(path).getTexture());
        _playerSprite.setTextureRect(sf::IntRect(
                0,
                0,
                _playersTextures.at(path).getRecX(),
                _playersTextures.at(path).getRecY()
        ));
        _playerSprite.setScale(_playersTextures.at(path).getScX(), _playersTextures.at(path).getScY());
    } else {
        Logger::getInstance()->error("Enemy texture not found for path: {}.", path);
    }
    _currentFrame = 2;
    _frameTimer = 0.0f;
    _animationSpeed = 0.1f;
    _movementDirection = MovementDirection::Default;
}

void PlayerSystem:: initOther(const std::string& path)
{
    if (_playersTextures.find(path) != _playersTextures.end()) {
        _text = _playersTextures.at(path);
        _other.setTexture(_playersTextures.at(path).getTexture());
        _other.setTextureRect(sf::IntRect(
                0,
                0,
                _playersTextures.at(path).getRecX(),
                _playersTextures.at(path).getRecY()
            ));
        _other.setScale(_playersTextures.at(path).getScX(), _playersTextures.at(path).getScY());
    } else {
        Logger::getInstance()->error("Enemy texture not found for path: {}.", path);
    }
}

void PlayerSystem::render(sf::RenderWindow& window, std::shared_ptr<Entity> entity, int crtplayerID)
{
    if (_isShootingGame == true)
        updateBulletAnimation();
    updatePlayerAnimation();
    if (entity->getId() == crtplayerID) {
        Logger::getInstance()->info("MY PLAYER RENDER");
        _playerSprite.setPosition(entity->getX(), entity->getY());
        window.draw(_playerSprite);
        if (_isShootingGame == true) {
            for (const auto& bullet : entity->getBullets()) {
                _bulletSprite.setPosition(bullet.getX(), bullet.getY());
                window.draw(_bulletSprite);
            }
        }
    } else {
        Logger::getInstance()->info("OTHER PLAYER RENDER");
        initOther(trimNulls(entity->getContent()));
        _other.setPosition(entity->getX(), entity->getY());
        window.draw(_other);
        if (_isShootingGame == true) {
            for (const auto& bullet : entity->getBullets()) {
                _bulletSprite.setPosition(bullet.getX(), bullet.getY());
                window.draw(_bulletSprite);
            }
        }
    }
}


void PlayerSystem::handleInput(const sf::Event& event, std::shared_ptr<Entity> crt_player, std::stack<SubtitleEvent>& stack)
{
    if (_isShootingGame == false) {
        if (event.type == sf::Event::KeyPressed) {
            if (event.key.code == sf::Keyboard::Space) {
                crt_player->setY(crt_player->getY() - (crt_player->getVel_y() + 20));
                stack.push(SubtitleEvent::PLAYER_UP);
            }
        } else if (event.type == sf::Event::KeyReleased) {
            stack.push(SubtitleEvent::PLAYER_DOWN);
        }
    } else {
        if (event.type == sf::Event::KeyPressed) {
            switch (event.key.code) {
                case sf::Keyboard::Up:
                    _movementDirection = MovementDirection::Up;
                    crt_player->setY(crt_player->getY() - crt_player->getVel_y());
                    _eventStack.push(GameEvent::PLAYER_UP);
                    stack.push(SubtitleEvent::PLAYER_UP);
                    break;
                case sf::Keyboard::Down:
                    _movementDirection = MovementDirection::Down;
                    crt_player->setY(crt_player->getY() + crt_player->getVel_y());
                    _eventStack.push(GameEvent::PLAYER_DOWN);
                    stack.push(SubtitleEvent::PLAYER_DOWN);
                    break;
                case sf::Keyboard::Left:
                    crt_player->setX(crt_player->getX() - crt_player->getVel_x());
                    _eventStack.push(GameEvent::PLAYER_LEFT);
                    stack.push(SubtitleEvent::PLAYER_LEFT);
                    break;
                case sf::Keyboard::Right:
                    crt_player->setX(crt_player->getX() + crt_player->getVel_x());
                    _eventStack.push(GameEvent::PLAYER_RIGHT);
                    stack.push(SubtitleEvent::PLAYER_RIGHT);
                    break;
                case sf::Keyboard::Space: {
                    crt_player->setIsShooting(true);
                    int bulletX = crt_player->getX() + 20;
                    int bulletY = crt_player->getY();
                    crt_player->addBullet(bulletX, bulletY, 10, 0);
                    _eventStack.push(GameEvent::SHOOT);
                    stack.push(SubtitleEvent::SHOOT);
                    break;
                }
                default:
                    stack.push(SubtitleEvent::DEFAULT);
                    break;
            }
        }
        if (event.type == sf::Event::KeyReleased) {
            _eventStack.push(GameEvent::DEFAULT);
            _movementDirection = MovementDirection::Default;
            if (event.key.code == sf::Keyboard::Space) {
                crt_player->setIsShooting(false);
            }
        }
    }
}

void PlayerSystem:: updatePlayerAnimation()
{
    _frameTimer += _clock.restart().asSeconds();
    if (_frameTimer >= _animationSpeed) {
        _frameTimer = 0.0f;

        if (_movementDirection == MovementDirection::Up) {
            _currentFrame++;
            if (_currentFrame > _playerText.getNbFrame() - 1)
               _currentFrame = _playerText.getNbFrame() - 1;
        } else if (_movementDirection == MovementDirection::Down) {
            _currentFrame--;
            if (_currentFrame < 0)
                _currentFrame = 0;
        } else if (_movementDirection == MovementDirection::Default) {
            _currentFrame = (_playerText.getNbFrame() - 1) / 2;
        }
    }

    int frameWidth = _playerText.getRecX();
    int frameHeight = _playerText.getRecY();
    _playerSprite.setTextureRect(sf::IntRect(_currentFrame * frameWidth, 0, frameWidth, frameHeight));
}

void PlayerSystem:: updateBulletAnimation()
{
    if ( _bulletTexture.getNbFrame() != 0) {
        _bulletFrameTimer += _bulletClock.restart().asSeconds();
        if (_bulletFrameTimer >= _bulletAnimationSpeed) {
            _bulletFrameTimer = 0.0f;
            std::cout << "BULLLET NB FRAME " << _bulletTexture.getNbFrame();
            if (_bulletTexture.getNbFrame()) {

            }
            _bulletCurrentFrame = (_bulletCurrentFrame + 1) % _bulletTexture.getNbFrame();

            int frameWidth = _bulletTexture.getRecX();
            int frameHeight = _bulletTexture.getRecY();

            _bulletSprite.setTextureRect(sf::IntRect(_bulletCurrentFrame * frameWidth, 0, frameWidth, frameHeight));
        }
    }
}
