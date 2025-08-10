#ifndef WIRES_H
#define WIRES_H

#include <ncurses.h>
#include "../windows/infowin.h"

void wires_regular(WINDOW* contentwin, WINDOW* miscwin, struct Bombattrs* bombattrs);
void wires_complex(WINDOW* contentwin, WINDOW* miscwin);
void wires_sequence(WINDOW* contentwin, WINDOW* miscwin);

#endif
