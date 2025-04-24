/*
** EPITECH PROJECT, 2025
** SFMLAudio.cpp
** File description:
** SFMLAudio
*/

#include "Audio/SFMLAudio.hpp"
#include <iostream>


extern "C"
{
    SFMLAudio *entry_point()
    {
        return new SFMLAudio();
    }
}

SFMLAudio::~SFMLAudio()
{
    stopAllSounds();
    stopBackgroundSound();
}

void SFMLAudio:: addSound(const GameEvent &event, const std::string& filePath)
{
    sf::SoundBuffer sound;
    if (!sound.loadFromFile(filePath)) {
        throw std::runtime_error("Failed to load sound file");
    }
    _soundBuffers[event] = std::move(sound);
    _soundBank[event] =  filePath;
}

void SFMLAudio:: playBackgroundSound(const GameEvent& event, bool loop)
{
    // no background music in loop
    if (_isBackgroundMusicPlay)
        return;
    if (_soundBank.find(event) == _soundBank.end()) {
        std::cerr << "error play background sound  not found"<< std::endl;
    }
    if (!_backgroundMusic.openFromFile(_soundBank[event])) {
        throw std::runtime_error("Failed to load sound file");
    }
    _backgroundMusic.setLoop(loop);
    _backgroundMusic.play();
    _isBackgroundMusicPlay = true;
}

void SFMLAudio:: stopBackgroundSound()
{
    _backgroundMusic.stop();
    _isBackgroundMusicPlay = false;

}

void SFMLAudio:: playSound(const GameEvent& event)
{
    auto it = _soundBuffers.find(event);
    if (it == _soundBuffers.end()) {
        throw std::runtime_error("Sound not found for this event");
    }

    auto sound = std::make_unique<sf::Sound>();
    sound->setBuffer(it->second);
    sound->play();
    _activeSounds.push_back(std::move(sound));
}

void SFMLAudio:: stopAllSounds()
{
    for (auto& sound : _activeSounds) {
        sound->stop();
    }
    _activeSounds.clear();
}