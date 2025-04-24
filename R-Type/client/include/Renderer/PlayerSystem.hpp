/*
** EPITECH PROJECT, 2024
** PlayerSystem
** File description:
** PlayerSystem
*/

#ifndef PLAYERSYSTEM_HPP_
#define PLAYERSYSTEM_HPP_

#include <SFML/Graphics.hpp>
#include <unordered_map>
#include <memory>
#include <stack>
#include "GameEvent.hpp"
#include "../EntityClient.hpp"
#include "AssetManager.hpp"

class PlayerSystem {

    public:
        PlayerSystem(const std::unordered_map<std::string, Texture>& bulletTextures,
        const std::unordered_map<std::string, Texture>& playersTextures, std::stack<GameEvent>& eventStack, bool& isShootingGame);
        ~PlayerSystem() = default;

        void initPlayer(const std::string& path);
        void initOther(const std::string& path);
        void render(sf::RenderWindow& window, std::shared_ptr<Entity> entity, int crtplayerID);
        void handleInput(const sf::Event& event, std::shared_ptr<Entity> crt_player, std::stack<SubtitleEvent>& stack);
        void initBulletSprite(const std::string& path);

    private:
        void updatePlayerAnimation(); 
        void updateBulletAnimation(); 

        enum class MovementDirection {
            Up,
            Down,
            Default,
        };
        bool& _isShootingGame;

        const std::unordered_map<std::string, Texture>& _playersTextures;
        Texture _playerText;
        sf::Sprite _playerSprite;
    
        Texture _text;
        sf::Sprite _other;
        
        Texture _bulletTexture;
        const std::unordered_map<std::string, Texture>& _bulletTextures;
        sf::Sprite _bulletSprite;
        
        MovementDirection _movementDirection = MovementDirection::Default;
        int _currentFrame = 0;
        sf::Clock _clock;
        float _frameTimer = 0.0f;
        float _animationSpeed = 0.1f;

        sf::Clock _bulletClock;
        int _bulletCurrentFrame = 0;
        float _bulletFrameTimer = 0.0f;
        float _bulletAnimationSpeed = 0.1f;
        std::stack<GameEvent>& _eventStack;
};

#endif /* !PLAYERSYSTEM_HPP_ */
