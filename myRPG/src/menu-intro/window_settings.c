/*
** EPITECH PROJECT, 2023
** window_settings
** File description:
** handle window settings for my_rpg menu
*/

#include "struct.h"
#include "intro_struct.h"
#include "intro_proto.h"

void window_size_settings(arg_t *arg)
{
    arg->mouse_pos = sfMouse_getPosition((sfWindow*)arg->window);
    sfVideoMode desktopMode = sfVideoMode_getDesktopMode();
    if (arg->event.type == sfEvtMouseButtonPressed
    && arg->mouse_pos.x >= 363 && arg->mouse_pos.x <= 400
    && arg->mouse_pos.y >= 254 && arg->mouse_pos.y <= 294) {
        sfRenderWindow_setSize(arg->window, (sfVector2u){630, 350});
    }
    if (arg->event.type == sfEvtMouseButtonPressed
    && arg->mouse_pos.x >= 405 && arg->mouse_pos.x <= 443
    && arg->mouse_pos.y >= 254 && arg->mouse_pos.y <= 294) {
        sfRenderWindow_setSize(arg->window, (sfVector2u){1430, 850});
    }
    if (arg->event.type == sfEvtMouseButtonPressed
    && arg->mouse_pos.x >= 447 && arg->mouse_pos.x <= 485
    && arg->mouse_pos.y >= 254 && arg->mouse_pos.y <= 294) {
        sfRenderWindow_setSize(arg->window,
        (sfVector2u){desktopMode.width, desktopMode.height});
    }
}

void window_settings_opt(arg_t *arg)
{
    window_size_settings(arg);
}
