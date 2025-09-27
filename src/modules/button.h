#ifndef BUTTON_H
#define BUTTON_H

#include <ncursesw/ncurses.h>
#include "../windows/infowin.h"
#include "../windows/miscwin.h"

// config for color labels
#include "../config.h"


#define ABORT 1
#define DETONATE 2
#define HOLD 3
#define PRESS 4

void button(WINDOW* contentwin, WINDOW* miscwin, struct Bombattrs* bombattrs);

#endif
