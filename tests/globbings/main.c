/*
** EPITECH PROJECT, 2024
** B-PSU-200-LIL-2-1-minishell1-matisse.dufour
** File description:
** main.c
*/
#include "my.h"
#include "minishell.h"
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>

void freeing(char *str, char **env)
{
    if (str)
        free(str);
    if (!env)
        return;
    for (int i = 0; env[i]; i++)
        free(env[i]);
    free(env);
}

int function(char *str, char ***env)
{
    if (my_strncmp(str, "cd", 2) == 0)
        return change_dir(str, env);
    if (my_strncmp(str, "setenv", 6) == 0)
        return set_environnement(str, env);
    if (my_strncmp(str, "unsetenv", 8) == 0)
        return delete_env(str, env);
    if (my_strncmp(str, "env", 3) == 0)
        return show_env(*env);
    return new_process(str, *env);
}

static void ttycheck(void)
{
    if (isatty(STDIN_FILENO))
        write(1, "$> ", 3);
}

void format_str(char *str)
{
    int i;

    for (i = 0; str[i]; i++) {
        if (str[i] == '\t')
            str[i] = ' ';
    }
    for (i = 0; str[i] && str[i] == ' '; i++);
    my_strcpy(str, str + i);
    if (str[my_strlen(str) - 1] == '\n')
        str[my_strlen(str) - 1] = '\0';
}

static void travel_command(char *str, char ***env, int *return_value,
    garbage_t *garbage)
{
    char **command = my_str_to_array(str, ";");

    garbage->command = command;
    for (int i = 0; command[i]; i++) {
        format_str(command[i]);
        if (my_strlen(command[i]) == 0)
            continue;
        *return_value = pipe_handling(command[i], env, garbage);
    }
    freeing(0, command);
}

/*int main(int argc, char **argv, char **env)
{
    char *str = 0;
    size_t len = 0;
    int return_value = 0;
    garbage_t garbage;

    env = copy_env(env);
    ttycheck();
    garbage.line = &str;
    garbage.env = &env;
    while (getline(&str, &len, stdin) != -1 && my_strcmp(str, "exit\n")) {
        insert_spaces(&str);
        travel_command(str, &env, &return_value, &garbage);
        ttycheck();
    }
    freeing(str, env);
    return return_value;
}*/

int main(void)
{
    arg_t *arg_un = malloc(sizeof(arg_t));
    arg_t *arg_deux = malloc(sizeof(arg_t));
    arg_t *arg_trois = malloc(sizeof(arg_t));

    arg_un->str = "lib/my/my*.c";
    arg_deux->str = "test[a-j]";
    arg_trois->str = "le monde";
    arg_un->next = arg_deux;
    arg_deux->next = arg_trois;
    arg_trois->next = NULL;
    globbings(&arg_un);
    for (arg_t *head = arg_un; head; head = head->next) {
        my_putstr(head->str);
        my_putstr("\n");
    }
    arg_t *next;
    for (arg_t *head = arg_un; head;) {
        next = head->next;
        free(head->str);
        free(head);
        head = next;
    }
}
