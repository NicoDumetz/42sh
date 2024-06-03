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

    garbage->return_value = built[i].built(str, garbage->env, garbage);
    free(str);
    return 1;
}

int check_built(char **command, garbage_t *garbage)
{
    if (command == NULL || command[0] == NULL)
        return 0;
    for (int i = 0; built[i].com; i++) {
        if (strcmp(command[0], built[i].com) == 0)
            return execute_builtins(command, i, garbage);
    }
    return 0;
}

static int execute_builtins_on_fork(char **command, int i, char ***env)
{
    char *str = array_to_str(command);

    if (strcmp(command[0], "env") == 0 ||
        (strcmp(command[0], "setenv") == 0 && command[1] == NULL)) {
        for (int i = 0; (*env)[i]; i++) {
            printf("%s\n", (*env)[i]);
        }
        free(str);
        exit(0);
    }
    free(str);
    exit(1);
    return 1;
}

int check_built_on_fork(char **command, char ***env)
{
    if (command == NULL || command[0] == NULL)
        return 0;
    for (int i = 0; built[i].com; i++) {
        if (strcmp(command[0], built[i].com) == 0)
            return execute_builtins_on_fork(command, i, env);
    }
    return 0;
}
