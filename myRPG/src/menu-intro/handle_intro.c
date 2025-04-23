/*
** EPITECH PROJECT, 2023
** handle_pages
** File description:
** handle pages displaying for my_rpg intro
*/

#include <stdio.h>
#include <stdlib.h>
#include "struct.h"
#include "intro_struct.h"
#include "intro_proto.h"
#include "my.h"
#include "init.h"
#include "game_menu.h"
#include "free.h"

void if_resume_game_clicked(arg_t *arg, intro_t *intro, game_menu_t *game_menu)
{
    if ((arg->event.type == sfEvtMouseButtonPressed
    && intro->mouse_pos.x >= 819 && intro->mouse_pos.x <= 1102
    && intro->mouse_pos.y >= 790 && intro->mouse_pos.y <= 900)
    || (arg->event.type == sfEvtKeyPressed
    && arg->event.key.code == sfKeyR)) {
        intro->in_menu_status = 0;
        intro->in_intro_status = 0;
        intro->in_game_status = 1;
        if (resume_game(arg) == 1)
            return;
        main_game(arg, intro, game_menu, 1);
    }
}

void slide_pages(arg_t *arg, intro_t *intro)
{
    if ((arg->event.type == sfEvtMouseButtonPressed && intro->status == 0
    && intro->mouse_pos.x >= 819 && intro->mouse_pos.x <= 1102
    && intro->mouse_pos.y >= 574 && intro->mouse_pos.y <= 700)
    || (arg->event.type == sfEvtKeyPressed
    && arg->event.key.code == sfKeyEnter)) {
        intro->status = 1;
    } else if ((intro->status != 0 && intro->status != 9)
    && (arg->event.type == sfEvtMouseButtonPressed
    || (arg->event.type == sfEvtKeyPressed
    && arg->event.key.code == sfKeySpace))) {
        intro->status++;
    } if (intro->status == 9
    && arg->event.type == sfEvtMouseButtonPressed
    && ((intro->mouse_pos.x >= 602 && intro->mouse_pos.x <= 830
    && intro->mouse_pos.y >= 853 && intro->mouse_pos.y <= 905)
    || (intro->mouse_pos.x >= 1023 && intro->mouse_pos.x <= 1254
    && intro->mouse_pos.y >= 853 && intro->mouse_pos.y <= 905))) {
        intro->status++;
    }
}

int pages_display_conditions_third(arg_t *arg, intro_t *intro,
buttons_t *buttons, game_menu_t *game_menu)
{
    if_resume_game_clicked(arg, intro, game_menu);
    if (intro->status == 8) {
        sfRenderWindow_drawSprite(arg->window,
        game_menu->command_list_sprite, NULL);
    } if (intro->status == 9) {
        sfRenderWindow_drawSprite(arg->window, intro->sprite_choose, NULL);
        draw_character_choice_rect(arg, buttons);
    } if (intro->status == 10) {
        arg->player = init_struct_player(arg->player_path,
        (sfVector2i) {358, 433}, (sfVector2f) {950.0f, 500.0f});
        intro->in_menu_status = 0;
        intro->in_intro_status = 0;
        intro->in_game_status = 1;
        if (main_game(arg, intro, game_menu, 0) == BACK_TO_MENU)
            return BACK_TO_MENU;
    } return (0);
}

int pages_display_conditions_second(arg_t *arg, intro_t *intro,
buttons_t *buttons, game_menu_t *game_menu)
{
    if (intro->status == 5) {
        sfRenderWindow_drawSprite(arg->window, intro->sprite5, NULL);
    } if (intro->status == 6) {
        sfRenderWindow_drawSprite(arg->window, intro->sprite6, NULL);
    } if (intro->status == 7) {
        sfRenderWindow_drawSprite(arg->window, intro->sprite7, NULL);
    }
    if (pages_display_conditions_third(arg, intro, buttons, game_menu)
    == BACK_TO_MENU)
        return BACK_TO_MENU;
    return (0);
}

int pages_display_conditions(arg_t *arg, intro_t *intro, buttons_t *buttons,
game_menu_t *game_menu)
{
    if (intro->status > 0) {
        sfRenderWindow_clear(arg->window, sfWhite);
        intro->in_menu_status = 0;
    } if (intro->status == 0) {
        sfRenderWindow_drawSprite(arg->window, intro->sprite_menu, NULL);
        intro->in_menu_status = 1;
    } if (intro->status == 1) {
        sfRenderWindow_drawSprite(arg->window, intro->sprite1, NULL);
    } if (intro->status == 2) {
        sfRenderWindow_drawSprite(arg->window, intro->sprite2, NULL);
    } if (intro->status == 3) {
        sfRenderWindow_drawSprite(arg->window, intro->sprite3, NULL);
    } if (intro->status == 4) {
        sfRenderWindow_drawSprite(arg->window, intro->sprite4, NULL);
    }
    return (pages_display_conditions_second(arg, intro, buttons, game_menu));
}
