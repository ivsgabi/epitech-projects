/*
** EPITECH PROJECT, 2023
** handle_buttons
** File description:
** fct to handle rect button on my_rpg intro
*/

#include "struct.h"
#include "intro_struct.h"
#include <stdlib.h>
#include "my.h"

void is_on_settings(arg_t *arg, intro_t *intro, buttons_t *buttons)
{
    sfColor sfTransBlack = sfColor_fromRGBA(0, 0, 0, 128);
    sfFloatRect settings_global =
        sfRectangleShape_getGlobalBounds(buttons->settings_rect);
    sfVector2i mouse_pos = sfMouse_getPosition((sfWindow *)arg->window);
    if (sfFloatRect_contains(&settings_global, mouse_pos.x, mouse_pos.y)) {
        buttons->settings_color = sfTransBlack;
        intro->dropdown_status = 1;
        if (arg->event.type == sfEvtMouseButtonPressed) {
            buttons->settings_color = sfTransBlack;
            intro->dropdown_status = 1;
            intro->is_clicked = 1;
        }
    } else if (intro->is_clicked == 0) {
        buttons->settings_color = sfTransparent;
        intro->dropdown_status = 0;
    }
}

void draw_setting_rect(arg_t *arg, intro_t *intro, buttons_t *buttons)
{
    sfRectangleShape_setFillColor(buttons->settings_rect,
    buttons->settings_color);
    sfRenderWindow_drawRectangleShape(arg->window,
    buttons->settings_rect, NULL);
    is_on_settings(arg, intro, buttons);
}

void is_on_quit(arg_t *arg, buttons_t *buttons)
{
    sfColor sfTransBlack = sfColor_fromRGBA(0, 0, 0, 128);
    sfFloatRect quit_global =
    sfRectangleShape_getGlobalBounds(buttons->quit_rect);
    sfVector2i mouse_pos = sfMouse_getPosition((sfWindow *)arg->window);
    if (sfFloatRect_contains(&quit_global, mouse_pos.x, mouse_pos.y)) {
        buttons->quit_color = sfTransBlack;
    } else {
        buttons->quit_color = sfTransparent;
    }
}

void draw_quit_rect(arg_t *arg, buttons_t *buttons)
{
    sfRectangleShape_setFillColor(buttons->quit_rect,
    buttons->quit_color);
    sfRenderWindow_drawRectangleShape(arg->window,
    buttons->quit_rect, NULL);
    is_on_quit(arg, buttons);
}
