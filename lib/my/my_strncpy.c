/*
** EPITECH PROJECT, 2023
** my_strncpy
** File description:
** copy the n first elements of src list into dest
*/
#include "my.h"

char *my_strncpy(char *dest, char const *str, int n)
{
    int i;

    for (i = 0; i < n; ++i) {
        dest[i] = str[i];
    }
    dest[i] = '\0';
    return (dest);
}
