/*
** EPITECH PROJECT, 2022
** rpg
** File description:
** display_all_btn.c
*/

#include "init.h"
#include "utils.h"
#include "struct.h"
#include "battle.h"
#include "display.h"

static void display_btn_name(arg_t *arg, text_t *name, int i)
{
    name->pos.x = arg->battle->battle_img[11]->pos.x + 200;
    name->pos.y = arg->battle->battle_img[11]->pos.y + 50;
    name->str = arg->inventory->pokemons[i]->name;
    display_text(arg, name);
}

static void display_btn_hp(arg_t *arg, text_t *name, int i)
{
    name->str = my_itoa(arg->inventory->pokemons[i]->hp);
    name->pos.x = arg->battle->battle_img[11]->pos.x + 160;
    name->pos.y = arg->battle->battle_img[11]->pos.y + 100;
    display_text(arg, name);
}

static void display_btn_save_hp(arg_t *arg, text_t *name, int i)
{
    name->str = my_itoa(arg->inventory->pokemons[i]->save_hp);
    name->pos.x = arg->battle->battle_img[11]->pos.x + 220;
    name->pos.y = arg->battle->battle_img[11]->pos.y + 100;
    display_text(arg, name);
}

static void display_btn_level(arg_t *arg, text_t *name, int i)
{
    name->str = my_itoa(arg->inventory->pokemons[i]->level);
    name->pos.x = arg->battle->battle_img[11]->pos.x + 470;
    name->pos.y = arg->battle->battle_img[11]->pos.y + 100;
    display_text(arg, name);
}

void display_all_btn(arg_t *arg, int nb)
{
    text_t *name = init_text((sfVector2f){0.0, 0.0}, sfBlack, 30);
    for (int i = 0; i < nb; i++) {
        change_pos_btn(arg, i);
        display_img(arg->battle->battle_img[11], arg->window);
        display_btn_name(arg, name, i);
        display_btn_hp(arg, name, i);
        display_btn_save_hp(arg, name, i);
        display_btn_level(arg, name, i);
        sfSprite_setScale(arg->inventory->pokemons[i]->f1->sprite,
        (sfVector2f) {1.5, 1.5});
        sfSprite_setTextureRect(arg->inventory->pokemons[i]->f1->sprite,
        arg->inventory->pokemons[i]->f1->rect);
        sfSprite_setPosition(arg->inventory->pokemons[i]->f1->sprite,
        (sfVector2f) {arg->battle->battle_img[11]->pos.x + 50,
        arg->battle->battle_img[11]->pos.y + 10});
        sfRenderWindow_drawSprite(arg->window,
        arg->inventory->pokemons[i]->f1->sprite, NULL);
        sfSprite_setScale(arg->inventory->pokemons[i]->f1->sprite,
        (sfVector2f) {3.5, 3.5});
    }
}
