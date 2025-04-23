/*
** EPITECH PROJECT, 2022
** rpg
** File description:
** main.c
*/

#include "my.h"
#include "free.h"
#include <stdlib.h>
#include <time.h>
#include "intro_proto.h"
#include "init.h"
#include "utils.h"

int main(int ac, char **)
{
    if (ac != 1)
        return 84;
    arg_t *arg = init_struct_arg();
    srand(time(0));
    if (arg == NULL)
        return 84;
    init_menu(arg);
}
    // free_all(arg);
