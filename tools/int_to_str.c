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
    char *buffer;
    int i = 0;

    buffer = malloc(my_intlen(nb) + 1);
    if (buffer == NULL)
        return NULL;
    if (nb == 0) {
        buffer[i] = '0';
        i++;
    } else {
        for (; nb > 0 && i < 100; i++) {
            buffer[i] = '0' + nb % 10;
            nb /= 10;
        }
    }
    buffer[i] = '\0';
    return my_revstr_convert(buffer);
}
