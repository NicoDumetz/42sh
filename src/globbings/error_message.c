/*
** EPITECH PROJECT, 2024
** B-PSU-200-LIL-2-1-42-matisse.dufour
** File description:
** fork.c
*/

#include "minishell.h"

void print_error_message_glob(char *arg)
{
    fprintf(stderr, "%s: No match.\n", arg);
}