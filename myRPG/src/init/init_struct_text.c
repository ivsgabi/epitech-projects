/*
** EPITECH PROJECT, 2022
** rpg
** File description:
** init_struct_text.c
*/

#include "struct.h"
#include "my.h"
#include "init.h"
#include <stdlib.h>


text_t *init_text(sfVector2f vector, sfColor color, int size)
{
    text_t *text = malloc(sizeof(*text));
    if (text == NULL)
        return NULL;
    text->text = sfText_create();
    text->font = sfFont_createFromFile("font/pokemon.ttf");
    text->pos = vector;
    text->is_visible = 0;
    text->str = "hello\0";
    sfText_setFont(text->text, text->font);
    sfText_setCharacterSize(text->text, size);
    sfText_setPosition(text->text, text->pos);
    sfText_setColor(text->text, color);
    return text;
}

text_t **init_all_text(void)
{
    text_t **text = malloc(sizeof(*text) * 4);
    for (int i = 0; i < 3; i++) {
        text[i] = init_text((sfVector2f) {300.0f, 850.0f},
        sfColor_fromRGB(70,130,180), 40);
    }
    text[3] = NULL;
    return text;
}

void init_str_text(arg_t *arg)
{
    arg->texts = init_all_text();
    char **text = read_map("config/text_pnj.txt");
    for (int i = 0; text[i] != NULL; i++) {
        arg->texts[i]->str = text[i];
    }
}

static void select_name_enemy_str(arg_t *arg, fight_t *fight)
{
    if (arg->battle->in_battle_master == 1) {
        fight->name_enemy->str =
        arg->battle->pokemon_maitre[arg->battle->num_pokemon]->name;
    } else {
        fight->name_enemy->str =
        arg->battle->all_pokemon[arg->battle->num_pokemon]->name;
    }
}

fight_t *init_struct_fight(arg_t *arg)
{
    fight_t *fight = malloc(sizeof(fight_t));
    if (fight == NULL)
        return NULL;
    fight->f1 = 0;
    fight->name = init_text((sfVector2f){1100, 680}, sfBlack, 35);
    fight->name_enemy = init_text((sfVector2f){550, 340}, sfBlack, 35);
    select_name_enemy_str(arg, fight);
    fight->life_enemy = init_text((sfVector2f){630, 380}, sfBlack, 30);
    fight->life = init_text((sfVector2f){1180, 720}, sfBlack, 30);
    fight->attack = init_text((sfVector2f){600, 910}, sfBlack, 40);
    fight->battle = init_text((sfVector2f) {700, 850}, sfBlack, 35);
    fight->battle->str = "attacks";
    fight->clock = sfClock_create();
    arg->battle->battle_img[4]->pos.x = 1000;
    arg->battle->battle_img[4]->pos.y = 850;
    return fight;
}
