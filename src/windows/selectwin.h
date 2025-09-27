#ifndef SELECT_H
#define SELECT_H

#include <stdbool.h>
#include <ncursesw/ncurses.h>
#include "../config.h"

WINDOW* create_selectwin();

void refresh_selectwin(WINDOW* selectwin, bool disabled);

#endif
