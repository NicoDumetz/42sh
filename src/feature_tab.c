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

feature_tab_t f_tab[] {
    {'|', (*pipe_feature)},
    {';', (*semi_col_feature)},
    {0, 0}
}
