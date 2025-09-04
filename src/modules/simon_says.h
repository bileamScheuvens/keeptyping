#ifndef SIMON_SAYS_H
#define SIMON_SAYS_H

#include <ncursesw/ncurses.h>
#include "../windows/infowin.h"
#include "../windows/miscwin.h"

void simon_says(WINDOW* contentwin, WINDOW* miscwin, struct Bombattrs* Bombattrs);

#endif
