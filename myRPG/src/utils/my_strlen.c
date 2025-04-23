/*
** EPITECH PROJECT, 2022
** rpg
** File description:
** my_strlen.c
*/

int my_strlen(char const *str)
{
    int compteur = 0;

    for (int i = 0; str[i] != '\0'; i += 1) {
        compteur += 1;
    }
    return compteur;
}

int my_strcmp(char *s1, char *s2)
{
    int i = 0;
    while (s1[i] && s2[i]){
        if (s1[i] == s2[i] && my_strlen(s1) == my_strlen(s2))
            i++;
        else
            return 1;
    }
    return 0;
}
