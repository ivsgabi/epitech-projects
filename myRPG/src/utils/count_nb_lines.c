/*
** EPITECH PROJECT, 2022
** rpg
** File description:
** count_nb_lines.c
*/

int count_nb_lines(char const *str)
{
    int count = 0;

    for (int i = 0; str[i] != '\0'; i += 1) {
        if (str[i] == '\n')
            count += 1;
    }
    return count;
}

int count_words(char const *str)
{
    int count = 1;

    for (int i = 0; str[i] != '\0'; i += 1) {
        if (str[i] == ';')
            count += 1;
    }
    return count;
}
