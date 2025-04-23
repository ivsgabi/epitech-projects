/*
** EPITECH PROJECT, 2022
** rpg
** File description:
** my_atof.c
*/

double my_atof(const char *str)
{
    double result = 0.0;
    double decimal = 0.0;
    int i = 0;
    int signe = 1;
    if (str[i] == '-') {
        signe = -1;
        i++;
    }
    for (;str[i] >= '0' && str[i] <= '9'; i++) {
        result = result * 10.0 + (str[i] - '0');
    }
    if (str[i] == '.') {
        i++;
        while (str[i] >= '0' && str[i] <= '9') {
            decimal = decimal * 10.0 + (str[i] - '0');
            i++;
        }
    }
    double value = result + decimal / 10.0;
    return signe * value;
}
