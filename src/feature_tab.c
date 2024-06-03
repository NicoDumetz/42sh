/*
** EPITECH PROJECT, 2024
** B-PSU-200-LIL-2-1-minishell1-matisse.dufour
** File description:
** feature_tab.c
*/

#include "my.h"
#include "minishell.h"
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>

redirection_tab_t r_tab[] = {
    {';', parsing_function},
    {0, 0}
};

lexing_tab_t l_tab[] = {
    {'`', &backtick_function},
    {'(', &backtick_function},
    {')', &backtick_function},
    {'*', &globbings_function},
    {'?', &globbings_function},
    {'[', &globbings_function},
    {']', &globbings_function},
    {'\\', &inhibitors_function},
    {'"', &inhibitors_function},
    {0, 0}
};
