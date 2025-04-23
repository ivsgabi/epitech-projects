/*
** EPITECH PROJECT, 2023
** rpg
** File description:
** move_player.h
*/

#ifndef MOVE_PLAYER_H
    #define MOVE_PLAYER_H

    #include "struct.h"

void move_player_up(arg_t *arg);
void move_player_down(arg_t *arg);
void move_player_left(arg_t *arg);
void move_player_right(arg_t *arg);
void move_pnj(player_t **pnj, img_t **obj_3d, int x, int y);

#endif /* MOVE_PLAYER_H */
