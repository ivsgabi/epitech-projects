/*
** EPITECH PROJECT, 2024
** KeyboardEvent
** File description:
** Arcade
*/

#include "Event/KeyboardEvent.hpp"

KeyboardEventType KeyboardEvent::getInput() const
{
    return this->_input;
}

void KeyboardEvent::setInput(KeyboardEventType input)
{
    this->_input = input;
}