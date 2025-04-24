/*
** EPITECH PROJECT, 2025
** IAudio.hpp
** File description:
** IAudio
*/

#ifndef IAUDIO_HPP_
#define IAUDIO_HPP_

#include <string>
#include "../Renderer/GameEvent.hpp"

class IAudio {
    public:
        virtual ~IAudio() = default;

        virtual void addSound(const GameEvent& event, const std::string& filePath) = 0;

        virtual void playSound(const GameEvent& event) = 0;

        virtual void playBackgroundSound(const GameEvent& event, bool loop) = 0;

        virtual void stopBackgroundSound() = 0;

        virtual void stopAllSounds() = 0;
};

#endif /* IAUDIO_HPP_ */

