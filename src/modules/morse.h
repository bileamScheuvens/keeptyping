#ifndef MORSE_H
#define MORSE_H

#include "../windows/infowin.h"
#include "../windows/miscwin.h"
#include <ncursesw/ncurses.h>

#define MAXLEN_MORSE 30

void morse(WINDOW *contentwin, WINDOW *miscwin);

#endif
