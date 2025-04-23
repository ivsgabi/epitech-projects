/*
** EPITECH PROJECT, 2024
** WindowEvent
** File description:
** Arcade
*/

#include "Event/WindowEvent.hpp"

void WindowEvent::setEvent(WindowEventType event)
{
    this->_event = event;
}

WindowEventType WindowEvent::getEvent() const
{
    return this->_event;
}