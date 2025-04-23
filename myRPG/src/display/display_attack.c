/*
** EPITECH PROJECT, 2022
** rpg
** File description:
** display_attack.c
*/

#include "struct.h"
#include "utils.h"
#include "display.h"
#include "battle.h"

void display_select_attack(arg_t *arg, fight_t *fight)
{
    sfMusic *attack = sfMusic_createFromFile("assets/attack.ogg");
    sfMusic_setVolume(attack, *arg->music_volume);
    while (sfRenderWindow_isOpen(arg->window)) {
        sfRenderWindow_pollEvent(arg->window, &arg->event);
        select_attack(arg);
        display_background_battle(arg, fight);
        display_battle_options(arg, fight);
        display_damage_attack(arg, fight->attack);
        display_elt_battle(arg, fight);
        display_text(arg, fight->life);
        if (attack_pressed(arg) == 0) {
            sfMusic_play(attack);
            return;
        }
        sfRenderWindow_display(arg->window);
    }
}

void display_attack(arg_t *arg, text_t *attack)
{
    pokemon_t *cho = arg->inventory->pokemons[arg->inventory->pokemon_choose];
    if (cho == NULL)
        return;
    for (int i = 0; i < 4; i++) {
        attack->str = cho->attack_names[i];
        if (i == 0) {
            attack->pos.x = 600;
            attack->pos.y = 850;
        } if (i == 1) {
            attack->pos.x = 600;
            attack->pos.y = 910;
        } if (i == 2) {
            attack->pos.x = 850;
            attack->pos.y = 850;
        } if (i == 3) {
            attack->pos.x = 850;
            attack->pos.y = 910;
        }
        display_text(arg, attack);
    }
}

void display_damage_attack(arg_t *arg, text_t *attack)
{
    if (arg->inventory->pokemons[arg->inventory->pokemon_choose] == NULL)
        return;
    display_img(arg->battle->battle_img[1], arg->window);
    display_attack(arg, attack);
    attack->pos.x = 1320;
    attack->pos.y = 860;
    pokemon_t *cho = arg->inventory->pokemons[arg->inventory->pokemon_choose];
    if (arg->battle->battle_img[4]->pos.x == 800 &&
    arg->battle->battle_img[4]->pos.y == 850)
        attack->str = my_itoa(cho->damage_attack[2]);
    if (arg->battle->battle_img[4]->pos.x == 800 &&
    arg->battle->battle_img[4]->pos.y == 910)
        attack->str = my_itoa(cho->damage_attack[3]);
    if (arg->battle->battle_img[4]->pos.x == 560 &&
    arg->battle->battle_img[4]->pos.y == 850)
        attack->str = my_itoa(cho->damage_attack[0]);
    if (arg->battle->battle_img[4]->pos.x == 560 &&
    arg->battle->battle_img[4]->pos.y == 910)
        attack->str = my_itoa(cho->damage_attack[1]);
    display_text(arg, attack);
}

void display_attack_wild_pokemon(arg_t *arg, fight_t *fight, text_t *text)
{
    display_img(arg->battle->battle_img[8], arg->window);
    display_text(arg, fight->life);
    display_text(arg, text);
    display_text(arg, fight->battle);
    sfText_setString(fight->name_enemy->text, fight->name_enemy->str);
    sfText_setPosition(fight->name_enemy->text, (sfVector2f) {550, 850});
    sfRenderWindow_drawText(arg->window, fight->name_enemy->text, NULL);
}
