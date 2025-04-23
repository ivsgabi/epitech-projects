/*
** EPITECH PROJECT, 2022
** rpg
** File description:
** display_battle.c
*/

#include "struct.h"
#include "display.h"
#include "utils.h"
#include "battle.h"

pokemon_t **select_pok(arg_t *arg)
{
    if (arg->battle->in_battle_master == 1)
        return arg->battle->pokemon_maitre;
    else
        return arg->battle->all_pokemon;
}

void display_battle(arg_t *arg, fight_t *fight)
{
    pokemon_t **pok = select_pok(arg);
    if (arg->inventory->pokemons[arg->inventory->pokemon_choose] == NULL)
        return;
    if (fight->f1 == 0) {
        display_img(pok[arg->battle->num_pokemon]->f1,
        arg->window);
    } else {
        display_img(pok[arg->battle->num_pokemon]->f2,
        arg->window);
    }
    fight->name->str =
    arg->inventory->pokemons[arg->inventory->pokemon_choose]->name;
    pokemon_t *p = arg->inventory->pokemons[arg->inventory->pokemon_choose];
    fight->life->str = my_itoa(p->hp);
    if (fight->f1 == 0) {
        display_img(p->dos_f1, arg->window);
    } else {
        display_img(p->dos_f2, arg->window);
    }
}

void display_background_battle(arg_t *arg, fight_t *fight)
{
    sfRenderWindow_clear(arg->window, sfBlack);
    manage_f1(fight);
    if (arg->battle->in_battle_master == 1)
        display_img(arg->battle->battle_img[17], arg->window);
    else
        display_img(arg->battle->battle_img[0], arg->window);
    display_battle(arg, fight);
    display_img(arg->battle->battle_img[5], arg->window);
    display_img(arg->battle->battle_img[6], arg->window);
}

void display_elt_battle(arg_t *arg, fight_t *fight)
{
    pokemon_t *p;
    if (arg->battle->in_battle_master == 1)
        p = arg->battle->pokemon_maitre[arg->battle->num_pokemon];
    else
        p = arg->battle->all_pokemon[arg->battle->num_pokemon];
    display_img(arg->battle->battle_img[4], arg->window);
    display_text(arg, fight->name_enemy);
    sfText_setColor(fight->name->text, sfBlack);
    display_text(arg, fight->name);
    fight->life_enemy->str = my_itoa(p->hp);
    display_text(arg, fight->life_enemy);
    display_battle_arene(arg);
}

void display_battle_options(arg_t *arg, fight_t *fight)
{
    display_img(arg->battle->battle_img[3], arg->window);
    sfText_setPosition(fight->name->text, (sfVector2f){600, 910});
    sfText_setString(fight->name->text, fight->name->str);
    sfText_setColor(fight->name->text, sfWhite);
    sfRenderWindow_drawText(arg->window, fight->name->text, NULL);
}
