/*
** EPITECH PROJECT, 2025
** GameEvent.hppp
** File description:
** GameEvent
*/

#ifndef GAMEEVENT_HPP_
#define GAMEEVENT_HPP_

enum class GameEvent {
    DEFAULT,
    PLAYER_UP,
    PLAYER_DOWN,
    PLAYER_LEFT,
    PLAYER_RIGHT,
    COLLISION,
    SHOOT,
    MENU_EVENT,
    GAME_EVENT,
    WIN_EVENT,
    DEAD_EVENT
};

enum class SubtitleEvent {
    DEFAULT,
    PLAYER_UP,
    PLAYER_DOWN,
    PLAYER_LEFT,
    PLAYER_RIGHT,
    COLLISION,
    SHOOT,
    WIN_EVENT,
    DEAD_EVENT
};

#endif /* !GAMEEVENT_HPP_ */
