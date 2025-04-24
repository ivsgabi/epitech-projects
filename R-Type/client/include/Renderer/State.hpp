/*
** EPITECH PROJECT, 2024
** State.hpp
** File description:
** State
*/

#ifndef STATE_HPP_
#define STATE_HPP_

#define WINDOW_WIDTH 1920
#define WINDOW_HEIGHT 1080

enum class GameStateRendering {
    QUIT_SERVER,
    QUIT_ROOM,
    MENU,
    MENU_OPT,
    ASSET_PLAYER,
    LEVELS,
    CONFIG_SUMMARY,
    ACCEPT,
    GAME,
    WIN,
    DEAD,
    HELP
};

#endif /* !STATE_HPP_ */
