/*
** EPITECH PROJECT, 2024
** execute built
** File description:
** execute built
*/

#include "my.h"
#include "minishell.h"
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>

static int execute_builtins(char **command, int i, garbage_t *garbage)
{
    char *str = array_to_str(command);

    garbage->return_value = built[i].built(str, garbage->env);
    free(str);
    return 1;
}

int check_built(char **command, garbage_t *garbage)
{
    for (int i = 0; built[i].com; i++) {
        if (strcmp(command[0], built[i].com) == 0)
            return execute_builtins(command, i, garbage);
    }
    return 0;
}

static int execute_builtins_on_fork(char **command, int i, char ***env)
{
    char *str = array_to_str(command);
    int ret = built[i].built(str, env);

    free(str);
    exit(ret);
    return 1;
}

int check_built_on_fork(char **command, char ***env)
{
    for (int i = 0; built[i].com; i++) {
        if (strcmp(command[0], built[i].com) == 0)
            return execute_builtins_on_fork(command, i, env);
    }
    return 0;
}
