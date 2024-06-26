/*
** EPITECH PROJECT, 2023
** my_strdup
** File description:
** duplicate and return a string terminated by \0
** it's at the programmer to free the returned str
*/
#include "my.h"
#include <stdlib.h>
#include <stdio.h>

char *my_strdup(const char *src)
{
    int size;
    char *dest;

    if (src == NULL)
        return NULL;
    size = my_strlen(src) + 1;
    dest = malloc(size);
    for (int i = 0; src[i] != '\0'; i++)
        dest[i] = src[i];
    dest[size - 1] = '\0';
    return dest;
}

char *my_gstrdup(const char *src)
{
    int size;
    char *dest;

    if (src == NULL)
        return NULL;
    size = my_strlen(src) + 1;
    dest = gmalloc(size);
    for (int i = 0; src[i] != '\0'; i++)
        dest[i] = src[i];
    dest[size - 1] = '\0';
    return dest;
}

char *my_gstrndup(const char *src, int index)
{
    char *dest;

    if (src == NULL)
        return NULL;
    dest = gmalloc(index + 1);
    for (int i = 0; i < index; i++)
        dest[i] = src[i];
    dest[index] = '\0';
    return dest;
}
