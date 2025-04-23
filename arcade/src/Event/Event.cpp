/*
** EPITECH PROJECT, 2024
** Event.cpp
** File description:
** Arcade
*/

#include "Event/Event.hpp"

Event::Event()
{
}

Event::~Event()
{
}

void Event::setEventType(EventType type)
{
    this->_eventType = type;
}

void Event::setMouseEvent(MouseEvent &event)
{
    this->_mouseEvent = event;
}

void Event::setWindowEvent(WindowEvent &event)
{
    this->_windowEvent = event;
}

void Event::setKeyboardEvent(KeyboardEvent &event)
{
    this->_keyboardEvent = event;
}

EventType Event::getEventType() const
{
    return this->_eventType;
}

MouseEvent Event::getMouseEvent() const
{
    return this->_mouseEvent;
}

WindowEvent Event::getWindowEvent() const
{
    return this->_windowEvent;
}

KeyboardEvent Event::getKeyboardEvent() const
{
    return this->_keyboardEvent;
}