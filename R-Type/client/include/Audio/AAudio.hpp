/*
** EPITECH PROJECT, 2025
** AAudio.hpp
** File description:
** AAudio
*/

#ifndef AAUDIO_HPP_
#define AAUDIO_HPP_

#include "IAudio.hpp"
#include <unordered_map>

class AAudio : public IAudio {
    protected:
        std::unordered_map<GameEvent, std::string> _soundBank;

    public:
        AAudio() = default;
        ~AAudio() override = default;

        void addSound(const GameEvent& event, const std::string& filePath) override {
            _soundBank[event] = filePath;
        }
};

#endif /* AAUDIO_HPP_ */
