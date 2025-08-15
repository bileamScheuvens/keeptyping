#ifndef WIRES_H
#define WIRES_H

#include <ncursesw/ncurses.h>
#include <math.h>
#include "../windows/infowin.h"
#include "../windows/miscwin.h"

void wires_regular(WINDOW* contentwin, WINDOW* miscwin, struct Bombattrs* bombattrs);
void wires_complex(WINDOW* contentwin, WINDOW* miscwin, struct Bombattrs* bombattrs);
void wire_sequence(WINDOW* contentwin, WINDOW* miscwin);

#endif
