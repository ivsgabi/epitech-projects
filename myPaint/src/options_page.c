/*
** EPITECH PROJECT, 2023
** options_page
** File description:
** function for displayin and handling options page
*/

#include <stdlib.h>
#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>
#include "../include/paint.h"

void display_options(struct window_t* window)
{
    window->texture2 =
    sfTexture_createFromFile("textures/options.png", NULL);
    window->options_sprite = sfSprite_create();

    sfVector2f scale_options = {1, 1};
    sfVector2f pos_options = {-36, 345};
    sfSprite_setTexture(window->options_sprite, window->texture2, sfTrue);
    sfSprite_setScale(window->options_sprite, scale_options);
    sfSprite_setPosition(window->options_sprite, pos_options);
}

int mouse_options(struct window_t* window, sfEvent event, int i)
{
    sfVector2i mouse = sfMouse_getPosition((sfWindow*)window->window);
    if (mouse.x >= 0 && mouse.x <= 105 &&
        mouse.y >= 470 && mouse.y <= 760) {
        if (event.type == sfEvtMouseButtonPressed) {
            display_options(window);
            i = 1;
        }
    } return (i);
}
