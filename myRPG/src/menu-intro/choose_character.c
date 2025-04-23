/*
** EPITECH PROJECT, 2023
** choose_character
** File description:
** for myrpg intro
*/

#include "struct.h"
#include "intro_struct.h"
#include <stdlib.h>

void is_on_boys(arg_t *arg, buttons_t *buttons)
{
    sfVector2i mouse_pos = sfMouse_getPosition((sfWindow *)arg->window);
    sfColor sfTransBlack = sfColor_fromRGBA(0, 0, 0, 128);
    sfFloatRect boys_global =
    sfRectangleShape_getGlobalBounds(buttons->boys_rect);
    if (sfFloatRect_contains(&boys_global, mouse_pos.x, mouse_pos.y)
    || (mouse_pos.x >= 598 && mouse_pos.x <= 827
    && mouse_pos.y >= 894 && mouse_pos.y <= 947)) {
        buttons->boys_color = sfTransBlack;
        arg->player_path = "assets/player_boy.png\0";
    } else {
        buttons->boys_color = sfTransparent;
    }
}

void is_on_girls(arg_t *arg, buttons_t *buttons)
{
    sfVector2i mouse_pos = sfMouse_getPosition((sfWindow *)arg->window);
    sfColor sfTransBlack = sfColor_fromRGBA(0, 0, 0, 128);
    sfFloatRect girls_global =
    sfRectangleShape_getGlobalBounds(buttons->girls_rect);
    if (sfFloatRect_contains(&girls_global, mouse_pos.x, mouse_pos.y)
    || (mouse_pos.x >= 1016 && mouse_pos.x <= 1247
    && mouse_pos.y >= 894 && mouse_pos.y <= 947)) {
        buttons->girls_color = sfTransBlack;
        arg->player_path = "assets/girl.png\0";
    } else {
        buttons->girls_color = sfTransparent;
    }
}

void draw_boys_rect(arg_t *arg, buttons_t *buttons)
{
    sfRectangleShape_setSize(buttons->boys_rect,
    buttons->boys_size);
    sfRectangleShape_setPosition(buttons->boys_rect,
    buttons->boys_pos);
    sfRectangleShape_setFillColor(buttons->boys_rect,
    buttons->boys_color);
    sfRenderWindow_drawRectangleShape(arg->window,
    buttons->boys_rect, NULL);
    is_on_boys(arg, buttons);
}

void draw_girls_rect(arg_t *arg, buttons_t *buttons)
{
    sfRectangleShape_setSize(buttons->girls_rect,
    buttons->boys_size);
    sfRectangleShape_setPosition(buttons->girls_rect,
    buttons->girls_pos);
    sfRectangleShape_setFillColor(buttons->girls_rect,
    buttons->girls_color);
    sfRenderWindow_drawRectangleShape(arg->window,
    buttons->girls_rect, NULL);
    is_on_girls(arg, buttons);
}

int draw_character_choice_rect(arg_t *arg, buttons_t *buttons)
{
    arg->player_path = "assets/player_boy.png\0";
    draw_boys_rect(arg, buttons);
    draw_girls_rect(arg, buttons);
    return (0);
}
