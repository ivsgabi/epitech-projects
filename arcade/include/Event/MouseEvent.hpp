/*
** EPITECH PROJECT, 2024
** Event.hpp
** File description:
** Event
*/

#ifndef MOUSE_EVENT_HPP_
#define MOUSE_EVENT_HPP_
#include "Entities/Entity.hpp"

enum MouseEventType {
    PRESSED,
    RELEASED,
    HOVER,
    NO_MOUSE_EVENT
};

class MouseEvent {
    public:
        MouseEvent() = default;
        ~MouseEvent() = default;
        void setPosition(std::pair<int, int> &position);
        std::pair<int, int> getPosition() const;
        void setState(MouseEventType state);
        MouseEventType getState() const;

    private:
        std::pair<int, int> _position; 
        MouseEventType _state;
};

#endif /* !MOUSE_EVENT_HPP_ */