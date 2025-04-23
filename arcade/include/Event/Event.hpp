/*
** EPITECH PROJECT, 2024
** Event.hpp
** File description:
** Event
*/

#ifndef EVENT_HPP_
#define EVENT_HPP_
#include "Event/KeyboardEvent.hpp"
#include "Event/MouseEvent.hpp"
#include "Event/WindowEvent.hpp"

enum EventType {
    MOUSE,
    KEYBOARD,
    WINDOW_E,
    NO_EVENT,
};

class Event {
    public:
        Event();
        ~Event();
        void setEventType(EventType type);
        void setMouseEvent(MouseEvent &event);
        void setWindowEvent(WindowEvent &event);
        void setKeyboardEvent(KeyboardEvent &event);
        EventType getEventType() const;
        MouseEvent getMouseEvent() const;
        WindowEvent getWindowEvent() const;
        KeyboardEvent getKeyboardEvent() const;

    private:
        EventType _eventType;
        MouseEvent _mouseEvent;
        WindowEvent _windowEvent;
        KeyboardEvent _keyboardEvent;
};

#endif /* !EVENT_HPP_ */