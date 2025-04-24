/*
** EPITECH PROJECT, 2025
** GameRendering.hpp
** File description:
** GameRendering
*/

#ifndef GAMERENDERING_HPP
#define GAMERENDERING_HPP

#include <SFML/Graphics.hpp>
#include <unordered_map>
#include <stack>
#include <memory>
#include "../EntityClient.hpp"
#include "State.hpp"
#include "GameEvent.hpp"
#include "AssetManager.hpp"
#include "BackgroundSystem.hpp"
#include "PlayerSystem.hpp"
#include "EnemySystem.hpp"
#include "SubtitleComp.hpp"
#include "../../../networking/include/Logger.hpp"

class GameRendering {
    public:
        GameRendering(AssetManager& assetManager, std::stack<GameStateRendering>& stateStack, std::stack<GameEvent>& eventStack, std::stack<SubtitleEvent>& subtitleStack, bool& isShooting);
        ~GameRendering() = default;

        void initialize(const std::unordered_map<int, std::shared_ptr<Entity>>& entities, int crt_playerID);

        void render(GameStateRendering crtState, sf::RenderWindow& window, const std::unordered_map<int, std::shared_ptr<Entity>>& entities, int crt_playerId);
        void handleInput(GameStateRendering crtState, const sf::Event& event, std::shared_ptr<Entity> crtPlayer, std::unordered_map<int, std::shared_ptr<Entity>>& entities);

    private:
        void renderDead(sf::RenderWindow& window, const std::unordered_map<int, std::shared_ptr<Entity>>& entities, int crt_playerId);
        void renderWin(sf::RenderWindow& window, const std::unordered_map<int, std::shared_ptr<Entity>>& entities, int crt_playerId);
        void renderGame(sf::RenderWindow& window, const std::unordered_map<int, std::shared_ptr<Entity>>& entities, int crt_playerId);
        void renderPopup(sf::RenderWindow& window, const std::string& title, sf::Color titleColor, const std::string& score, const std::string& level);

        void handleGameKeysInput(const sf::Event& event);
        void handleEndGame(const std::unordered_map<int, std::shared_ptr<Entity>>& entities);
        void handleUserInput(const sf::Event& event, std::shared_ptr<Entity> crtPlayer);
        void handleEndGameKeysInput(const sf::Event& event);

        AssetManager& _assetManager;
        std::stack<GameStateRendering>& _stateStack;
        std::stack<GameEvent>& _eventStack;
        std::stack<SubtitleEvent>& _subtitleEventStack;

        std::shared_ptr<BackgroundSystem> _backgroundSystem;
        std::shared_ptr<PlayerSystem> _playerSystem;
        std::shared_ptr<EnemySystem> _enemySystem;

        bool& _isShootingGame;

        SubtitleComp _subtitles;

        sf::RectangleShape _blurOverlay;
        sf::Text _scoreText;
        sf::Text _levelText;
        sf::RectangleShape _popupBox;
        sf::Text _popupTitle;
        sf::Text _popupScore;
        sf::Text _popupLevel;
        sf::Text _popupInstruction;

        sf::Sprite _shortcutSprite;
        sf::Texture _shortcutTexture;
        bool _showShortcutPopup = false;

        sf::Sprite _infoSprite;
        sf::Texture _infoTexture;
        int _crtPlayerID = -1;
};

#endif // GAMERENDERING_HPP

