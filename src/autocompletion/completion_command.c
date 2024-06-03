/*
** EPITECH PROJECT, 2024
** B-PSU-200-LIL-2-1-42sh-nicolas.dumetz
** File description:
** completion_command.c
*/

#include "../../include/minishell.h"
#include <unistd.h>

static void set_completed(char **completed, char *name)
{
    char *copy = malloc(sizeof(char) * (strlen(name) + 2));

    copy = strcpy(copy, name);
    copy = strcat(copy, " ");
    *completed = strdup(copy);
    free(copy);
}

static void read_command_dir(DIR *dir, int *count, char *word, char **compiled)
{
    struct dirent *dp;

    dp = readdir(dir);
    while (dp != NULL) {
        if (*count > 1)
            return;
        if (my_strncmp(dp->d_name, word, strlen(word)) == 0) {
            set_completed(compiled, dp->d_name);
            (*count)++;
        }
        dp = readdir(dir);
    }
}

static int search_command(char *word, char **compiled)
{
    char *path = getenv("PATH");
    char **path_tokens = my_str_to_word_array_char(path, ":");
    int count = 0;
    DIR *dir;

    for (int i = 0; path_tokens[i] != NULL; i++) {
        dir = opendir(path_tokens[i]);
        if (dir != NULL) {
            read_command_dir(dir, &count, word, compiled);
            closedir(dir);
        }
    }
    return count;
}

void auto_completion_command(char *word, char **line, getline_t *getmy,
    int len)
{
    char *completed = NULL;
    int count = search_command(word, &completed);

    if (count == 0)
        return;
    if (count == 1) {
        complete_command(line, completed, len, getmy);
    } else {
        if (getmy->word != NULL){
            free(getmy->word);
            getmy->word = NULL;
        }
        getmy->word = my_strdup(word);
        getmy->tab = 1;
    }
    if (completed != NULL)
        free(completed);
}

void exec_or_command(char *word, char **line, getline_t *getmy, int len)
{
    if (word[0] == '.' || word[0] == '/')
        auto_completion_file(word, line, getmy);
    else
        auto_completion_command(word, line, getmy, len);
}
