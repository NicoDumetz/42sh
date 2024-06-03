/*
** EPITECH PROJECT, 2024
** int to str
** File description:
** int to str
*/
#include "minishell.h"

static char *my_revstr_convert(char *str)
{
    int index;
    int len = my_strlen(str) - 1;
    char temp;

    for (index = 0; index < len; index++) {
        temp = str[index];
        str[index] = str[len];
        str[len] = temp;
        len--;
    }
    return str;
}

int my_intlen(long nb)
{
    int compt = 0;

    if (nb < 0) {
        nb = nb * -1;
        compt++;
    }
    if (nb == 0)
        return compt + 1;
    for (int i; nb > 0; i++) {
        compt++;
        nb /= 10;
    }
    return compt;
}

char *int_to_str(int nb)
{
    char *buffer = malloc(my_intlen(nb) + 1);
    int i = 0;

    if (nb == 0) {
        buffer[i] = '0';
        buffer[i + 1] = '0';
        i += 2;
    } else {
        for (i; nb != 0 && i < 100; i++) {
            buffer[i] = '0' + nb % 10;
            nb /= 10;
        }
        if (i == 1) {
            buffer[i] = '0';
            i++;
        }
    }
    buffer[i] = '\0';
    return my_revstr_convert(buffer);
}
