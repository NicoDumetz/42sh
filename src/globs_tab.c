/*
** EPITECH PROJECT, 2024
** B-PSU-200-LIL-2-1-minishell1-matisse.dufour
** File description:
** glob.c
*/

#include "my.h"
#include "minishell.h"
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>

lexing_tab_t l_tab[] = {
    {'*', globbings_function},
    {'?', globbings_function},
    {91, globbings_function},
    {93, globbings_function},
    {0, 0}
};
