/*
** EPITECH PROJECT, 2023
** MY_STRCAT
** File description:
** concatenates two strings
*/

#include "my.h"

char *my_memcat(char *dest, char const *src)
{
    char *str = NULL;
    int i = 0;
    int j = 0;

    str = malloc(sizeof(char) * (my_strlen(dest) +
        my_strlen(src) + 1));
    str = my_strcpy(str, dest);
    for (i = 0; dest[i]; i++) {
        str[i] = dest[i];
    }
    j = i;
    for (j = 0; src[j]; j++) {
        str[i] = src[j];
        i++;
    }
    str[i] = '\0';
    free(dest);
    return str;
}
