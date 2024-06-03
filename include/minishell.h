/*
** EPITECH PROJECT, 2024
** B-PSU-200-LIL-2-1-minishell1-matisse.dufour
** File description:
** minishell.h
*/

#ifndef MINISHELL_HEADER
    #define MINISHELL_HEADER
    #include "my.h"
    #include <stdlib.h>
    #include <string.h>
    #include <stdbool.h>
    #define IS_ALPHA(c) (('a' <= c && c <= 'z') || ('A' <= c && c <= 'Z'))
    #define IS_NUM(c) ('0' <= c && c <= '9')

typedef enum lexing_s {
    TERM_T = 0,
    ARG_T,
    SPACE_T,
    SEMI_COL_T,
    PIPE_T,
    PARENTHESIS_LEFT_T,
    PARENTHESIS_RIGHT_T,
    REDIRECT_LEFT_T,
    REDIRECT_RIGHT_T,
    SINGLE_QUOTE,
    DOUBLE_QUOTE_T,
    BACKSLASH_T,
    BACKSLASH_N_T,
    BACkSLASH_T_T,
    STAR_T,
    SQUARE_BRACKET_LEFT_T,
    SQUARE_BRACKET_RIGHT_T,
    AND_T,
    EXCLAM_POINT,
    BACKTICK
} lexing_t;

typedef struct token_s {
    char sep;
    char *arg;
    int index;
    struct token_s *prev;
    struct token_s *next;
} token_t;

typedef struct garbage_s {
    char ***env;
    char **line;
    char **command;
    int save_in;
    int save_out;
    void *history;
    char *raw_command;
    int return_value;
    token_t **token_list;
} garbage_t;

token_t **init_token_list(char *str);
char **token_to_str_array(token_t *start, int end);
void insert_spaces(char **input);
void freeing(char *str, char **board);
void format_str(char *str);
int function(char *str, char ***env);
int change_dir(char *str, char ***env);
char **copy_env(char **env);
int show_env(char **env);
int set_environnement(char *str, char ***env);
int delete_env(char *str, char ***env);
int new_process(char *str, char **env);
int pipe_handling(char *str, char ***env, garbage_t *garbage);
void pipe_redirect(int i, int num_pipe, int pipeline[][2]);
void fork_pipes(char **pipes, int pipeline[][2], int num_pipe,
    garbage_t *garbage);
int redirection(char *str, char ***env, int save_out);
int redirection_errors(char *command, char **pipes, int i);
int command_errors(char *str, char **pipes, int save_in, int save_out);
#endif
