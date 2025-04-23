/*
** EPITECH PROJECT, 2023
** settings_opt
** File description:
** for menu my_rpg
*/

#include "struct.h"
#include "intro_struct.h"
#include "intro_proto.h"

void if_cross_clicked(arg_t *arg, intro_t *intro, buttons_t *buttons)
{
    sfVector2i mouse_pos = sfMouse_getPosition((sfWindow*)arg->window);
    if (arg->event.type == sfEvtMouseButtonPressed
    && mouse_pos.x >= 125 && mouse_pos.x <= 156
    && mouse_pos.y >= 136 && mouse_pos.y <= 164) {
        buttons->settings_color = sfTransparent;
        intro->dropdown_status = 0;
        intro->is_clicked = 0;
    }
}

void if_sound_clicked(arg_t *arg, intro_t *intro, buttons_t *buttons)
{
    sfVector2i mouse_pos = sfMouse_getPosition((sfWindow *)arg->window);
    if (arg->event.type == sfEvtMouseButtonPressed
    && mouse_pos.x >= 241 && mouse_pos.x <= 327
    && mouse_pos.y >= 161 && mouse_pos.y <= 212) {
        buttons->settings_color = sfTransparent;
        intro->dropdown_status = 1;
        intro->is_clicked = 2;
    }
}

void if_window_clicked(arg_t *arg, intro_t *intro, buttons_t *buttons)
{
    sfVector2i mouse_pos = sfMouse_getPosition((sfWindow *)arg->window);
    if (arg->event.type == sfEvtMouseButtonPressed
    && mouse_pos.x >= 338 && mouse_pos.x <= 422
    && mouse_pos.y >= 161 && mouse_pos.y <= 212) {
        buttons->settings_color = sfTransparent;
        intro->dropdown_status = 1;
        intro->is_clicked = 3;
    }
}

void if_ssounds_close_is_clicked(arg_t *arg, intro_t *intro,
buttons_t *buttons)
{
    sfVector2i mouse_pos = sfMouse_getPosition((sfWindow *)arg->window);
    if (arg->event.type == sfEvtMouseButtonPressed
        && mouse_pos.x >= 250 && mouse_pos.x <= 405
        && mouse_pos.y >= 388 && mouse_pos.y <= 418) {
            buttons->settings_color = sfTransparent;
            intro->is_clicked = 1;
    }
}

void if_swindow_close_is_clicked(arg_t *arg, intro_t *intro,
buttons_t *buttons)
{
    sfVector2i mouse_pos = sfMouse_getPosition((sfWindow *)arg->window);
    if (arg->event.type == sfEvtMouseButtonPressed
        && mouse_pos.x >= 248 && mouse_pos.x <= 421
        && mouse_pos.y >= 321 && mouse_pos.y <= 355) {
            buttons->settings_color = sfTransparent;
            intro->is_clicked = 1;
    }
}
