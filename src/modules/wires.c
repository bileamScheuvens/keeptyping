#include "wires.h"

void wires_regular(WINDOW* contentwin, WINDOW* miscwin){
  mvwprintw(miscwin, 2, 1, "regular selected");
  wrefresh(miscwin);
}

void wires_complex(WINDOW* contentwin, WINDOW* miscwin){
  mvwprintw(miscwin, 2, 1, "complex selected");
  wrefresh(miscwin);
}

void wires_sequence(WINDOW* contentwin, WINDOW* miscwin){
  mvwprintw(miscwin, 2, 1, "sequence selected");
  wrefresh(miscwin);
}

