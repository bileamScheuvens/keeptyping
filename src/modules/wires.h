#ifndef WIRES_H
#define WIRES_H

#include <ncurses.h>

void wires_regular(WINDOW* contentwin, WINDOW* miscwin);
void wires_complex(WINDOW* contentwin, WINDOW* miscwin);
void wires_sequence(WINDOW* contentwin, WINDOW* miscwin);

#endif
