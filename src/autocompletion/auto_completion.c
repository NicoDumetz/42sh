/*
** EPITECH PROJECT, 2024
** B-PSU-200-LIL-2-1-42sh-nicolas.dumetz
** File description:
** auto_completion.c
*/

#include "../../include/minishell.h"
#include <unistd.h>

static void get_chars_before_cursor(const char *line, int len_before, char
    *result)
{
    int i;

    for (i = 0; i < len_before; i++) {
        result[i] = line[i];
    }
    result[i] = '\0';
}

static int count_words(const char *line)
{
    int count = 0;
    int j = 0;

    for (int i = 0; line[i] != '\0';) {
        while (line[i + j] != '\0' && line[i + j] != ' '
            && line[i + j] != '\t')
            j++;
        if (j != 0) {
            count++;
            i += j;
        } else
            i++;
        j = 0;
    }
    if (count != 0 && line[strlen(line) - 1] == ' ')
        count++;
    return count;
}

void complete_command(char **line, char *completed, int len,
    getline_t *getmy)
{
    int letter = 0;
    int len_completed = my_strlen(completed);
    int i;

    for (i = (len - 1) - getmy->cursor; i - letter >= 0 && (*line)[i -
    letter] != ' '; letter++);
    if ((int) getmy->n < len + len_completed - letter + 2) {
        *line = realloc(*line, sizeof(char) *
            (len + len_completed - letter + 2));
        if (*line == NULL)
            return;
    }
    for (i = letter; i < len_completed; i++)
        insert_char(*line, completed[i], len + i - letter, len -
            getmy->cursor + i - letter);
}

void tab_command(char **line, int len, getline_t *getmy)
{
    char *com_before_curs = malloc(sizeof(char) * (len - getmy->cursor + 1));
    char **tab_word;
    int count_word;

    if (com_before_curs == NULL)
        return;
    get_chars_before_cursor(*line, len - getmy->cursor, com_before_curs);
    count_word = count_words(com_before_curs);
    tab_word = my_str_to_minishell_array(com_before_curs, " \t");
    if (count_word == 1)
        exec_or_command(tab_word[0], line, getmy, len);
    else
        completion_file(tab_word, line, count_word, getmy);
    for (int i = 0; tab_word[i] != 0; i++)
        free(tab_word[i]);
    free(tab_word);
    free(com_before_curs);
}
