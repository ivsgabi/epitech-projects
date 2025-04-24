/*
** EPITECH PROJECT, 2025
** SFMLAudio.hpp
** File description:
** SFMLAudio
*/

#ifndef SFMLAUDIO_HPP_
#define SFMLAUDIO_HPP_

#include "AAudio.hpp"
#include <SFML/Audio.hpp>
#include <memory>
#include <vector>
#include <unordered_map>


class SFMLAudio : public AAudio {
    private:
        sf::Music _backgroundMusic;
        std::vector<std::unique_ptr<sf::Sound>> _activeSounds;
        std::unordered_map<GameEvent, sf::SoundBuffer> _soundBuffers;
        bool _isBackgroundMusicPlay = false;
    public:
        SFMLAudio() = default;
        ~SFMLAudio() override;
        void addSound(const GameEvent &event, const std::string& filePath) override;
        void playBackgroundSound(const GameEvent& event, bool loop) override;
        void stopBackgroundSound() override;

        void playSound(const GameEvent& event) override;
        void stopAllSounds() override;
};

#endif /* !SFMLAUDIO_HPP_ */
