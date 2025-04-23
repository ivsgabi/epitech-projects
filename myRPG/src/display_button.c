/*
** EPITECH PROJECT, 2022
** rpg
** File description:
** display_button.c
*/

#include "struct.h"
#include "my.h"
#include "utils.h"
#include "init.h"
#include "display.h"
#include <stdlib.h>

void display_button_text(arg_t *arg, int index)
{
    char **file = read_map("config/first_pokemon_intro.txt");
    text_t *text = init_text((sfVector2f) {300.0f, 850.0f},
    sfColor_fromRGB(70,130,180), 40);
    char *str = NULL;
    if (index == 0) {
        str = my_strcat(file[0], "\n");
        str = my_strcat(str, file[1]);
    } else if (index == 1) {
        str = my_strcat(file[2], "\n");
        str = my_strcat(str, file[3]);
    } else {
        str = my_strcat(file[4], "\n");
        str = my_strcat(str, file[5]);
    }
    text->str = str;
    sfRenderWindow_drawSprite(arg->window, arg->text_box->sprite, NULL);
    display_text(arg, text);
    free(text);
}

void display_button_hover(arg_t *arg, sfSprite *pokemon_hover,
sfSprite *pokemon_clicked, int index)
{
    sfRenderWindow_drawSprite(arg->window, pokemon_hover, NULL);
    if (arg->event.type == sfEvtMouseButtonPressed)
    sfRenderWindow_drawSprite(arg->window, pokemon_clicked, NULL);
    display_button_text(arg, index);
}

int display_btn_bulbizarre(arg_t *arg, choose_t *choose, sfVector2i mouse)
{
    sfRenderWindow_drawSprite(arg->window, choose->bulbi, NULL);
    if (mouse.x >= 400 && mouse.x <= 400 + 390 && mouse.y >= 300 &&
        mouse.y <= 300 + 382) {
        display_button_hover(arg, choose->bulbi_hover,
        choose->bulbi_clicked, 0);
        if (arg->event.type == sfEvtMouseButtonReleased) {
            add_pokemon_to_inventory(arg, 0, arg->battle->all_pokemon[0]);
            return 1;
        }
    }
    return 0;
}

int display_btn_salameche(arg_t *arg, choose_t *choose, sfVector2i mouse)
{
    sfRenderWindow_drawSprite(arg->window, choose->salam, NULL);
    if (mouse.x >= 800 && mouse.x <= 800 + 390 && mouse.y >= 300 &&
        mouse.y <= 300 + 382) {
        display_button_hover(arg, choose->salam_hover,
        choose->salam_clicked, 1);
        if (arg->event.type == sfEvtMouseButtonReleased) {
            add_pokemon_to_inventory(arg, 0, arg->battle->all_pokemon[1]);
            return 1;
        }
    }
    return 0;
}

int display_btn_carapuce(arg_t *arg, choose_t *choose, sfVector2i mouse)
{
    sfRenderWindow_drawSprite(arg->window, choose->cara, NULL);
    if (mouse.x >= 1200 && mouse.x <= 1200 + 390 && mouse.y >= 300 &&
        mouse.y <= 300 + 382) {
        display_button_hover(arg, choose->cara_hover, choose->cara_clicked, 2);
        if (arg->event.type == sfEvtMouseButtonReleased){
            add_pokemon_to_inventory(arg, 0, arg->battle->all_pokemon[2]);
            return 1;
        }
    }
    return 0;
}
