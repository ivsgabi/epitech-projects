/*
** EPITECH PROJECT, 2024
** MenuModule header
** File description:
** arcade
*/

#ifndef MENUMODULE_HPP_
    #define MENUMODULE_HPP_
#include "GameModules/AGameModule.hpp"
#include "ListModules.hpp"
#include "Exceptions/Exceptions.hpp"

class MenuModule : public AGameModule {
    public:
        MenuModule();
        ~MenuModule();
        void initGame() override;
        void exitGame() override;
        void handleEvent(const Event &event) override;
        void setEntities(std::map<std::size_t, std::shared_ptr<Entity>>) override;
        std::map<std::size_t, std::shared_ptr<Entity>>getEntities() const override;
        GameStatus getStatus() const override;
        void setStatus(GameStatus status) override;
        void setEvent(Event &event) override;
        Event &getEvent() override;

    private:
        std::pair<std::size_t, std::size_t> _listGamesIndexes;
        std::pair<std::size_t, std::size_t> _listGraphicsIndexes;
        std::size_t _currentGameIndex;
        std::size_t _currentGraphicIndex;
        std::size_t _playerNameIndex;
        void handleSelectionGame(const Event &event);
        void handleInputPlayerName(const Event &event);
        std::vector<std::string> _listGames;
        std::vector<std::string> _listGraphics;
        const std::unordered_map<KeyboardEventType, std::string> _alphabetLetters =
        {
            { KeyboardEventType::A, "A" },
            { KeyboardEventType::B, "B" },
            { KeyboardEventType::C, "C" },
            { KeyboardEventType::D, "D" },
            { KeyboardEventType::E, "E" },
            { KeyboardEventType::F, "F" },
            { KeyboardEventType::G, "G" },
            { KeyboardEventType::H, "H" },
            { KeyboardEventType::I, "I" },
            { KeyboardEventType::J, "J" },
            { KeyboardEventType::K, "K" },
            { KeyboardEventType::L, "L" },
            { KeyboardEventType::M, "M" },
            { KeyboardEventType::N, "N" },
            { KeyboardEventType::O, "O" },
            { KeyboardEventType::P, "P" },
            { KeyboardEventType::Q, "Q" },
            { KeyboardEventType::R, "R" },
            { KeyboardEventType::S, "S" },
            { KeyboardEventType::T, "T" },
            { KeyboardEventType::U, "U" },
            { KeyboardEventType::V, "V" },
            { KeyboardEventType::W, "W" },
            { KeyboardEventType::X, "X" },
            { KeyboardEventType::Y, "Y" },
            { KeyboardEventType::Z, "Z" },
        };
};

#endif /* !IGAME_MODULE_HPP_ */