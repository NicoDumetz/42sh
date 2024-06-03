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

char **copy_env(char **env)
{
    char **new_env;
    int i = 0;

    for (; env[i]; i++);
    new_env = malloc(sizeof(char *) * (i + 1));
    for (i = 0; env[i]; i++)
        new_env[i] = my_strdup(env[i]);
    new_env[i] = 0;
    return new_env;
}

int show_env(char *, char ***env, garbage_t *)
{
    for (int i = 0; (*env)[i]; i++) {
        printf("%s\n", (*env)[i]);
    }
    return 0;
}

static int delete_errors(char **command)
{
    int i = 0;

    for (; command[i]; i++);
    if (i < 2) {
        write(2, "unsetenv: Too few arguments.\n", 29);
        freeing(0, command);
        return 1;
    }
    return 0;
}

static int check_deletion(char **env, int actual_size, int *new_size,
    char **command)
{
    char *name = 0;

    for (int i = 1; command[i]; i++) {
        name = malloc(my_strlen(command[i]) + 2);
        my_strcpy(name, command[i]);
        my_strcat(name, "=");
        if (my_strncmp(name, env[actual_size],
        my_strlen(name)) == 0) {
            free(name);
            return 1;
        }
        free(name);
    }
    if (new_size)
        *new_size += 1;
    return 0;
}

static char **new_env(char **env, char **command, int new_size)
{
    char **new_env = malloc(sizeof(char *) * (new_size + 1));
    int j = 0;

    for (int i = 0; env[i]; i++) {
        if (check_deletion(env, i, 0, command))
            free(env[i]);
        else {
            new_env[j] = env[i];
            j++;
        }
    }
    new_env[j] = 0;
    free(env);
    return new_env;
}

int delete_env(char *str, char ***env, garbage_t *)
{
    char **command;
    int new_size = 0;
    int actual_size = 0;

    command = my_str_to_array(str, " ");
    if (delete_errors(command))
        return 1;
    for (; (*env)[actual_size]; actual_size++)
        check_deletion(*env, actual_size, &new_size, command);
    if (new_size == actual_size) {
        freeing(0, command);
        return 0;
    }
    *env = new_env(*env, command, new_size);
    freeing(0, command);
    return 0;
}
