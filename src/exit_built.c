/*
** EPITECH PROJECT, 2024
** B-PSU-200-LIL-2-1-minishell1-matisse.dufour
** File description:
** env.c
*/

#include <stdlib.h>
#include <unistd.h>
#include "my.h"
#include "minishell.h"

static int is_num(char *str)
{
    int i = 0;

    for (i = 0; str[i] && (str[i] == '-' || str[i] == '+'); i++);
    for (; str[i]; i++)
        if (str[i] > '9' || str[i] < '0')
        return 0;
    return 1;
}

int find_true_value_neg(int raw_value)
{
    int true_value = 256;

    for (int i = 0; i > raw_value; i--) {
        true_value--;
        if (true_value == -1)
            true_value = 255;
    }
    return true_value;
}

int find_true_value_pos(int raw_value)
{
    int true_value = 0;

    for (int i = 0; i < raw_value; i++) {
        true_value++;
        if (true_value == 256)
            true_value = 0;
    }
    return true_value;
}

int find_value(char *str)
{
    int raw_value = -1;

    if (is_num(str)) {
        raw_value = my_getnbr(str);
        if (raw_value >= 0)
            raw_value = find_true_value_pos(raw_value);
        else
            raw_value = find_true_value_neg(raw_value);
    }
    return raw_value;
}

int exit_built(char *str, char ***, garbage_t *garbage, pipeline_t *)
{
    char **arg = my_str_to_array(str, " ");
    int value = 0;

    if (tab_len(arg) > 2) {
        fprintf(stderr, "exit: Expression Syntax.\n");
        return 1;
    }
    if (tab_len(arg) == 2) {
        value = find_value(arg[1]);
        if (value < 0) {
            fprintf(stderr, "exit: Expression Syntax.\n");
            return 1;
        }
    } else
        value = garbage->return_value;
    cleanup(garbage);
    gmalloc(0);
    exit(value);
}
