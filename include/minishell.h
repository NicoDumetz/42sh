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
    #include <glob.h>
    #include <stdio.h>
    #define IS_ALPHA(c) (('a' <= c && c <= 'z') || ('A' <= c && c <= 'Z'))
    #define IS_NUM(c) ('0' <= c && c <= '9')

typedef struct alias_s {
    char *name;
    char *com;
    struct alias_s *next;
} alias_t;

typedef struct var_s {
    char *var;
    char *value;
    struct var_s *next;
} var_t;

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
    alias_t *alias;
    var_t *local;
} garbage_t;

typedef struct redirection_tab_s {
    char sep;
    int (*redirection)(garbage_t *, token_t **);
} redirection_tab_t;

typedef struct lexing_tab_s {
    char sep;
    int (*lexing)(garbage_t *, token_t **);
} lexing_tab_t;

extern redirection_tab_t r_tab[];

extern lexing_tab_t l_tab[];

token_t **init_token_list(char *str);

void lexing_features(garbage_t *garbage, token_t **token_list);

int parsing_function(garbage_t *garbage, token_t **token_list);

int globbings_function(garbage_t *garbage, token_t **token_list);

int new_process(char **command, char **env);

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
int pipe_handling(char *str, char ***env, garbage_t *garbage);
void pipe_redirect(int i, int num_pipe, int pipeline[][2]);
void fork_pipes(char **pipes, int pipeline[][2], int num_pipe,
    garbage_t *garbage);
int redirection(char *str, char ***env, int save_out);
int redirection_errors(char *command, char **pipes, int i);
int command_errors(char *str, char **pipes, int save_in, int save_out);
int set_alias(char *name, char *command, garbage_t *garbage);
void free_alias(garbage_t *garbage);
char *check_alias(char *token, garbage_t *garbage);
void unalias(char *name, garbage_t *garbage);
int set_local(char *var, char *value, garbage_t *garbage);
void unset_var(char *name, garbage_t *garbage);
void free_var(garbage_t *garbage);
char *check_local(char *token, garbage_t *garbage);
#endif
