/*
** EPITECH PROJECT, 2024
** B-PSU-200-LIL-2-1-42sh-nicolas.dumetz
** File description:
** non_canonical_mode.c
*/

#include <termios.h>
#include <unistd.h>
#include <stdlib.h>

void set_non_canonical_mode(void)
{
    struct termios term;

    if (tcgetattr(STDIN_FILENO, &term) == -1) {
        return;
    }
    term.c_lflag &= ~(ICANON | ECHO);
    term.c_cc[VMIN] = 1;
    term.c_cc[VTIME] = 0;
    if (tcsetattr(STDIN_FILENO, TCSANOW, &term) == -1) {
        return;
    }
}

void set_canonical_mode(void)
{
    struct termios term;

    tcgetattr(STDIN_FILENO, &term);
    term.c_lflag |= (ICANON | ECHO);
    term.c_cc[VMIN] = 0;
    term.c_cc[VTIME] = 0;
    tcsetattr(STDIN_FILENO, TCSANOW, &term);
}
