/*
** EPITECH PROJECT, 2024
** builtins_tab
** File description:
** builtins
*/

#include "my.h"
#include "minishell.h"
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>

builtins_t built[] = {
    {"env", show_env},
    {"setenv", set_environnement},
    {"unsetenv", delete_env},
    {"cd", change_dir},
    {"alias", set_alias},
    {"unalias", unalias},
    {"set", set_local},
    {"unset", unset_var},
    {"history", history_command},
    {0, 0}
};
