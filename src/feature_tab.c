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
    {0, 0}
};
