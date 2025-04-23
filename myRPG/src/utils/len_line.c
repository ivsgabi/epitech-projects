/*
** EPITECH PROJECT, 2022
** rpg
** File description:
** len_line.c
*/

int len_line(char const *str, int start)
{
    int count = 0;

    for (int i = start; str[i] != '\n'; i += 1, count += 1);
    return count;
}

int len_words(char const *str, int start)
{
    int count = 0;

    for (int i = start; str[i] != ';' && str[i] != '\0'; i++, count++);
    return count;
}
