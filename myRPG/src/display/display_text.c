/*
** EPITECH PROJECT, 2022
** rpg
** File description:
** display_text.c
*/

#include "struct.h"
#include "display.h"

void display_text(arg_t *arg, text_t *text)
{
    sfText_setString(text->text, text->str);
    sfText_setPosition(text->text, text->pos);
    sfRenderWindow_drawText(arg->window, text->text, NULL);
}

void display_text_box(arg_t *arg, sfRenderWindow *window)
{
    for (int i = 0; arg->texts[i] != NULL; i++) {
        if (arg->texts[i]->is_visible == 1) {
            display_img(arg->text_box, window);
            display_text(arg, arg->texts[i]);
        }
    }
}
