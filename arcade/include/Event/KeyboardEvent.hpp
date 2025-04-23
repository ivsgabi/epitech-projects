/*
** EPITECH PROJECT, 2024
** Event.hpp
** File description:
** Event
*/

#ifndef KEYBOARD_EVENT_HPP_
#define KEYBOARD_EVENT_HPP_
#include "Entities/Entity.hpp"

enum KeyboardEventType { LEFT, RIGHT, UP, DOWN, NEXT_GRAPHICAL,
            NEXT_GAME, RESTART, GO_BACK_MENU, EXIT,
            A, B, C, D, E, F, G, H, I, J, K, L, M, N, O, P, Q, R,
            S, T, U, V, W, X, Y, Z, NO_KEYBOARD_EVENT };

class KeyboardEvent {
    public:
        KeyboardEvent() = default;
        ~KeyboardEvent() = default;
        void setInput(KeyboardEventType input);
        KeyboardEventType getInput() const;

    private:
        KeyboardEventType _input;
};

#endif /* !KEYBOARD_EVENT_HPP_ */