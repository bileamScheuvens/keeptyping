#ifndef SELECT_H
#define SELECT_H

#include <stdbool.h>
#include <ncurses.h>

WINDOW* create_selectwin();

void refresh_selectwin(WINDOW* selectwin, bool disabled);

#endif
