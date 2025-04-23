/*
** EPITECH PROJECT, 2023
** rpg
** File description:
** display.h
*/

#ifndef DISPLAY_H
    #define DISPLAY_H

    #include "struct.h"

void display_img(img_t *img, sfRenderWindow *window);
void display_all_img(arg_t *arg, sfRenderWindow *window);
void display_text_box(arg_t *arg, sfRenderWindow *window);
void display_text(arg_t *arg, text_t *text);
void display_battle(arg_t *arg, fight_t *fight);
void display_damage_attack(arg_t *arg, text_t *attack);
void display_background_battle(arg_t *arg, fight_t *fight);
void display_attack(arg_t *arg, text_t *attack);
void display_elt_battle(arg_t *arg, fight_t *fight);
void display_battle_options(arg_t *arg, fight_t *fight);
void display_attack_wild_pokemon(arg_t *arg, fight_t *fight, text_t *text);
void display_select_attack(arg_t *arg, fight_t *fight);
int display_bag(arg_t *arg, fight_t *fight);
void display_all_btn(arg_t *arg, int nb);
void display_inventary(arg_t *arg);
void display_succeed_capture(arg_t *arg, fight_t *fight);
void display_fail_capture(arg_t *arg, fight_t *fight);
void display_all_pokemon(arg_t *arg);
void display_intro(arg_t *arg);
void display_battle_arene(arg_t *arg) ;
void display_end_of_battle(arg_t *arg, fight_t *fight, text_t *text_end);
int display_btn_bulbizarre(arg_t *arg, choose_t *choose, sfVector2i mouse);
int display_btn_salameche(arg_t *arg, choose_t *choose, sfVector2i mouse);
int display_btn_carapuce(arg_t *arg, choose_t *choose, sfVector2i mouse);

#endif /* DISPLAY_H */
