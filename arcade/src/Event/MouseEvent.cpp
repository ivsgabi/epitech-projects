/*
** EPITECH PROJECT, 2024
** MouseEvent
** File description:
** Arcade
*/

#include "Event/MouseEvent.hpp"

void MouseEvent::setPosition(std::pair <int, int> &position)
{
    this->_position = position;
}

std::pair<int, int> MouseEvent::getPosition() const
{
    return this->_position;
}

void MouseEvent::setState(MouseEventType state)
{
    this->_state = state;
}

MouseEventType MouseEvent::getState() const
{
    return this->_state;
}