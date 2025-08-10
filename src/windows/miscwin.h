#ifndef MISC_H
#define MISC_H

#include <ncurses.h>

WINDOW* create_miscwin();
void log_to_misc(WINDOW* miscwin, char *content);
void log_to_misc_many(WINDOW* miscwin, char *content[], int count);

#endif
