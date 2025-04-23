/*
** EPITECH PROJECT, 2023
** button_handling
** File description:
** handle buttons for my paint
*/

#include "../include/paint.h"

void button_file(window_t *window)
{
    window->sfTransBlack = sfColor_fromRGBA(0, 0, 0, 128);
    window->button_file = sfRectangleShape_create();
    sfRectangleShape_setSize(window->button_file, (sfVector2f) {467, 80});
    sfRectangleShape_setPosition(window->button_file, (sfVector2f) {1251, 52});
    sfRectangleShape_setFillColor(window->button_file, sfTransparent);
    window->texture3 =
    sfTexture_createFromFile("textures/file-dropdown.png", NULL);
    window->dropdown1 = sfSprite_create();
    sfVector2f scale_dropdown1 = {0.6, 0.6};
    sfVector2f pos_dropdown1 = {1216, 105};
    sfSprite_setTexture(window->dropdown1, window->texture3, sfTrue);
    sfSprite_setScale(window->dropdown1, scale_dropdown1);
    sfSprite_setPosition(window->dropdown1, pos_dropdown1);
    button_file_opt(window);
}

void button_file_opt(window_t *window)
{
sfVector2i mouse_pos = sfMouse_getPosition((sfWindow*)window->window);
    if (mouse_pos.x >= 1250 && mouse_pos.x <= 1720 &&
        mouse_pos.y >= 50 && mouse_pos.y <= 130) {
            sfRectangleShape_setFillColor(window->button_file,
            window->sfTransBlack);
            sfRenderWindow_drawSprite(window->window, window->dropdown1, NULL);
        } else {
    sfRenderWindow_drawRectangleShape(window->window,
    window->button_file, NULL);
    } if (mouse_pos.x >= 1250 && mouse_pos.x <= 1720 &&
        mouse_pos.y >= 50 && mouse_pos.y <= 130 &&
        window->event.type == sfEvtMouseButtonPressed) {
            sfRenderWindow_drawSprite(window->window, window->dropdown1, NULL);
            window->status = 3;
        }
}
