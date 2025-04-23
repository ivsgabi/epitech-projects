/*
** EPITECH PROJECT, 2023
** init
** File description:
** for mypaint
*/

#include <stdlib.h>
#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>
#include "../include/paint.h"

sfBool is_in(struct window_t *window, sfVector2i mouse_pos)
{
    if (sfRectangleShape_getGlobalBounds(window->back).left <= mouse_pos.x &&
        sfRectangleShape_getGlobalBounds(window->back).left
        + sfRectangleShape_getGlobalBounds(window->back).width >= mouse_pos.x &&
        sfRectangleShape_getGlobalBounds(window->back).top <= mouse_pos.y &&
        sfRectangleShape_getGlobalBounds(window->back).top
        + sfRectangleShape_getGlobalBounds(window->back).height >= mouse_pos.y)
        return sfTrue;
    return sfFalse;
}

void init_colors(colors_t *colors)
{
    colors->black = (sfVector2f){47, 47};
    colors->black_size = (sfVector2f){190, 190};
    colors->white = (sfVector2f){1070, 47};
    colors->white_size = (sfVector2f){135, 200};
    colors->green = (sfVector2f){250, 47};
    colors->green_size = (sfVector2f){190, 190};
    colors->red = (sfVector2f){460, 47};
    colors->red_size = (sfVector2f){190, 190};
    colors->blue = (sfVector2f){660, 47};
    colors->blue_size = (sfVector2f){190, 190};
    colors->pen = (sfVector2f){895, 47};
    colors->pen_size = (sfVector2f){135, 200};
}

void main_loop(struct window_t *window)
{
    colors_t *colors = malloc(sizeof(colors_t));
    t_point *points = NULL;
    init_colors(colors);
    window->circle = sfCircleShape_create();
    window->thickness = 6.f;
    window->current_color = sfBlack;
    window->status = 0;
    window->draw_circle = sfFalse;
    sfVector2i mouse_pos;
    while (sfRenderWindow_isOpen(window->window)) {
        while (sfRenderWindow_pollEvent(window->window, &window->event)) {
            handle_events(window, colors, &mouse_pos);
            window->draw_circle && is_in(window, mouse_pos) ?
            insert_elem(window, &points, mouse_pos.x, mouse_pos.y) : 0;
        } display(window, &points);
        sfRenderWindow_display(window->window);
    } free_list(&points);
}

int init_csfml(void)
{
    struct window_t *window = malloc(sizeof(struct window_t));
    if (window == NULL) {
        my_putstr("error : window struct malloc failed\n");
        return (84);
    }
    sfVideoMode video_mode = {1920, 1080, 32};
    window->texture1 =
        sfTexture_createFromFile("textures/paint-base.jpg", NULL);
    window->base_sprite = sfSprite_create();
    sfVector2f scale_base = {1, 1};
    window->window =
        sfRenderWindow_create(video_mode, "my_paint", sfResize | sfClose, NULL);
    sfSprite_setTexture(window->base_sprite, window->texture1, sfTrue);
    sfSprite_setScale(window->base_sprite, scale_base);
    main_loop(window);
    free(window);
    return (0);
}
