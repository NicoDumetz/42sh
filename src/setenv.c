/*
** EPITECH PROJECT, 2024
** B-PSU-200-LIL-2-1-minishell1-matisse.dufour
** File description:
** setenv.c
*/
#include "my.h"
#include "minishell.h"
#include <stdlib.h>
#include <unistd.h>

static int invalid_name(char *str)
{
    for (int i = 0; str[i]; i++) {
        if (!IS_ALPHA(str[i]) && !IS_NUM(str[i]) && str[i] != '_' &&
        str[i] != '.')
            return 1;
    }
    return 0;
}

static int setenv_error(char **command, int i)
{
    if (i > 3) {
        write(2, "setenv: Too many arguments.\n", 28);
        freeing(0, command);
        return 1;
    }
    if (!IS_ALPHA(command[1][0]) && command[1][0] != '_') {
        write(2, "setenv: Variable name must begin with a letter.\n", 48);
        freeing(0, command);
        return 1;
    }
    if (invalid_name(command[1])) {
        write(2, "setenv: ", 8);
        write(2, "Variable name must contain alphanumeric characters.\n", 52);
        freeing(0, command);
        return 1;
    }
    return 0;
}

static int already_exist(char **command, char **env, int *i)
{
    char *search;

    for (*i = 0; env[*i]; *i += 1) {
        search = malloc(my_strlen(command[1]) + 2);
        my_strcpy(search, command[1]);
        my_strcat(search, "=");
        if (my_strncmp(env[*i], search, my_strlen(search)) == 0) {
            free(search);
            return 1;
        }
        free(search);
    }
    return 0;
}

static void replace_env(char **command, char **env, int i)
{
    int size_var = (command[2] != 0) ? my_strlen(command[2]) : 0;
    char *str_var = (command[2] != 0) ? command[2] : "";

    if (env[i] != 0)
        free(env[i]);
    env[i] = malloc(my_strlen(command[1]) + size_var + 2);
    my_strcpy(env[i], command[1]);
    my_strcat(env[i], "=");
    my_strcat(env[i], str_var);
}

static char **add_env(char **command, char **env)
{
    int env_size;
    char **new_env;

    for (env_size = 0; env[env_size]; env_size++);
    new_env = malloc(sizeof(char *) * (env_size + 2));
    for (env_size = 0; env[env_size]; env_size++)
        new_env[env_size] = env[env_size];
    new_env[env_size] = 0;
    replace_env(command, new_env, env_size);
    new_env[env_size + 1] = 0;
    free(env);
    return new_env;
}

int set_environnement(char *str, char ***env, garbage_t *garbage)
{
    char **command;
    int i;

    command = my_str_to_array(str, " ");
    for (i = 0; command[i]; i++);
    if (i == 1) {
        freeing(0, command);
        return show_env(str, env, garbage);
    }
    if (setenv_error(command, i))
        return 1;
    if (already_exist(command, *env, &i))
        replace_env(command, *env, i);
    else
        *env = add_env(command, *env);
    freeing(0, command);
    return 0;
}
