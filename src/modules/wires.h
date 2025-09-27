#ifndef WIRES_H
#define WIRES_H

#include <ncursesw/ncurses.h>
#include <math.h>
#include "../windows/infowin.h"
#include "../windows/miscwin.h"
#include "../config.h"

#define SEQRED 0
#define SEQBLUE 1
#define SEQBLACK 2
#define DESTA 100
#define DESTB 10
#define DESTC 1

void wires_regular(WINDOW* contentwin, WINDOW* miscwin, struct Bombattrs* bombattrs);
void wires_complex(WINDOW* contentwin, WINDOW* miscwin, struct Bombattrs* bombattrs);
void wire_sequence(WINDOW* contentwin, WINDOW* miscwin);

#endif
