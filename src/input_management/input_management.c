/*
** EPITECH PROJECT, 2024
** B-PSU-200-LIL-2-1-42sh-nicolas.dumetz
** File description:
** input_management.c
*/

#include "stdio.h"

int is_end(char **line, int len)
{
    (*line)[len] = '\n';
    (*line)[len + 1] = '\0';
    return (int)len + 1;
}

void is_del(char **line, int len)
{
    if (len > 0) {
        (*line)[len - 1] = '\0';
        printf("\b \b");
    }
}