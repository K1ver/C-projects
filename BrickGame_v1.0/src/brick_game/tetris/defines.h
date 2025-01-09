#ifndef DEFINES_H
#define DEFINES_H

#include <ncurses.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

#define WIN_INIT(time)     \
  {                        \
    initscr();             \
    noecho();              \
    curs_set(0);           \
    keypad(stdscr, TRUE);  \
    nodelay(stdscr, TRUE); \
  }
#define MVPRINTW(y, x, ...) mvprintw(0 + (y), 0 + (x), __VA_ARGS__)
#define ROWS_MAP 20
#define COLS_MAP 10

#endif