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
    {";", execute_semicolon},
    {"\n", execute_semicolon},
    {"|", execute_pipe},
    {">", execute_redirection},
    {"<", execute_redirection},
    {"<<", execute_redirection},
    {">>", execute_redirection},
    // {"||", execute_or},
    // {"&", execute_single_and},
    // {"&&", execute_and},
    {0, 0}
};

lexing_tab_t l_tab[] = {
    // {'`', lexing = &backtick_function},
    // {'(', lexing = &backtick_function},
    // {')', lexing = &backtick_function},
    {'*', globbings_function},
    {'?', globbings_function},
    {'[', globbings_function},
    {']', globbings_function},
    // {'\\', lexing = &inhibitors_function},
    // {'"', lexing = &inhibitors_function},
    {0, 0}
};
