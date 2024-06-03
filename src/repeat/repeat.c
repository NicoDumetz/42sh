/*
** EPITECH PROJECT, 2024
** repeat
** File description:
** repeat
*/

#include "my.h"
#include "minishell.h"
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>


static void execute(char *com, garbage_t *garbage, int laps)
{
    pipeline_t **pip;
    size_t com_length = strlen(com);
    char *com_with_newline = malloc(com_length + 2);

    strcpy(com_with_newline, com);
    com_with_newline[com_length] = '\n';
    com_with_newline[com_length + 1] = '\0';
    pip = init_pipeline(com_with_newline);
    format_variable(garbage, pip);
    free(com_with_newline);
    for (int i = 0; i < laps; i++)
        process_execution(garbage, pip);
    free_pipeline(pip);
}

int repeat(char *str, char ***env, garbage_t *garbage)
{
    int laps = my_getnbr(str + strlen("repeat") + 1);
    char *com = str + strlen("repeat") + 1 + my_intlen(laps);

    format_str(com);
    printf("%s\n", com);
    if (com == NULL || com[0] == '\n')
        printf("caca\n");
    return 0;
}
