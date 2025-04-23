/*
** EPITECH PROJECT, 2024
** Event.hpp
** File description:
** Event
*/

#ifndef WINDOW_EVENT_HPP_
#define WINDOW_EVENT_HPP_

enum WindowEventType {
    RESIZED,
    CLOSED,
    NO_WINDOW_EVENT
};

class WindowEvent {
    public:
        WindowEvent() = default;
        ~WindowEvent() = default;
        void setEvent(WindowEventType event);
        WindowEventType getEvent() const;

    private:
        WindowEventType _event;
} ;

#endif /* !WINDOW_EVENT_HPP_ */