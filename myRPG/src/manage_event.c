/*
** EPITECH PROJECT, 2022
** rpg
** File description:
** manage_event.c
*/

#include "my.h"
#include "struct.h"
#include <stdlib.h>
#include "game_menu.h"
#include "intro_struct.h"
#include "init.h"
#include "utils.h"
#include "battle.h"

void teleportation(arg_t *arg)
{
    if (arg->map[arg->player->pos.y][arg->player->pos.x] == 'R') {
        teleportation_retour(arg);
        return;
    }
    if (teleportation_house(arg) == 1)
        return;
    if (teleportation_center(arg) == 1)
        return;
    if (teleportation_shop(arg) == 1)
        return;
    if (teleportation_arene(arg) == 1)
        return;
}

void lancement_combat_arene(arg_t *arg, intro_t *intro, game_menu_t *game_menu)
{
    sfView_zoom(arg->view, 2.0f);
    sfRenderWindow_setView(arg->window, arg->view);
    display_intro(arg);
    arg->battle->in_battle_master = 1;
    sfView_zoom(arg->view, 0.5f);
    teleportation_retour(arg);
    sfRenderWindow_setView(arg->window, arg->view);
    if (start_fight(arg) == 5) {
        display_window(arg, intro, game_menu, &intro->music);
        heal_pokemon(arg->inventory->pokemons, arg);
    }
}

static void can_move_player(arg_t *arg, intro_t *intro, game_menu_t *game_menu)
{
    if (arg->can_move != 0) {
        if (move_player(arg) == 5) {
            display_window(arg, intro, game_menu, &intro->music);
            heal_pokemon(arg->inventory->pokemons, arg);
        }
    }
}

static void manage_building(arg_t *arg, intro_t *intro, game_menu_t *game_menu)
{
    if (arg->map[arg->player->pos.y][arg->player->pos.x] == '2')
            lancement_combat_arene(arg, intro, game_menu);
    if (arg->map[arg->player->pos.y][arg->player->pos.x] == '3' &&
    arg->event.type == sfEvtKeyPressed &&
    arg->event.key.code == sfKeyEnter) {
        heal_pokemon(arg->inventory->pokemons, arg);
    }
    if (arg->map[arg->player->pos.y][arg->player->pos.x] == '4' &&
    arg->event.type == sfEvtKeyPressed &&
    arg->event.key.code == sfKeyEnter) {
        shop(arg);
    }
}

void manage_event(arg_t *arg, intro_t *intro, game_menu_t *game_menu)
{
    int check;
    while (sfRenderWindow_pollEvent(arg->window, &arg->event)) {
        check = 0;
        if (arg->event.type == sfEvtClosed ||
        (arg->event.type == sfEvtKeyPressed &&
        arg->event.key.code == sfKeyQ))
            sfRenderWindow_close(arg->window);
        when_display_game_menu(arg, intro, game_menu);
        can_move_player(arg, intro, game_menu);
        teleportation(arg);
        check = close_text_box(arg, check);
        (check == 0) ? speak_to_pnj(arg) : 0;
        manage_building(arg, intro, game_menu);
    }
}
