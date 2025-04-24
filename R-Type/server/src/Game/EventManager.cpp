/*
** EPITECH PROJECT, 2025
** EventManager
** File description:
** RType
*/

#include "Game/EventManager.hpp"

// EventManager::EventManager() {}

// EventManager::~EventManager() {}

// EventManager *EventManager::on(const std::string &event_name, void (*callback)(T *game))
// {
//     std::vector<void (*)(IGame *game)> *listeners = &events[event_name];

//     if (std::find(listeners->begin(), listeners->end(), callback) != listeners->end()) {
//         return this;
//     }
//     listeners->push_back(callback);
//     return this;
// }

// bool EventManager::emit(const std::string &event_name, IGame *game)
// {
//     std::vector<void (*)(IGame *game)> listeners = events[event_name];

//     if (listeners.size() == 0)
//         return false;

//     for (int idx = 0; idx < listeners.size(); idx += 1){
//         listeners[idx](game);
//     }

//     return true;
// }