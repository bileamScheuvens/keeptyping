#include "stdio.h"
#include "string.h"
#include <ncursesw/ncurses.h>
#include <stdbool.h>



struct LedConfig {
  bool leds[12];
  char position[5];
}

struct LedConfig configs[] = {
  {{false, false, true, false, true, true, true, true, true, true, false, true}, "Up"},
  {{true, false, true, false, true, false, false, true, true, false, true, true}, "Up"},
  {{false, true, true, false, false, true, true, true, true, true, false, true}, "Down"},
  {{true, false, true, false, true, false, false, true, false, false, false, true}, "Down"},
  {{false, false, false, false, true, false, true, false, false, true, true, true}, "Left"},
  {{false, false, false, false, true, false, false, false, false, true, true, false}, "Left"},
  {{true, false, true, true, true, true, true, true, true, false, true, false}, "Right"},
  {{true, false, true, true, false, false, true, true, true, false, true, false}, "Right"}
}


void knob(WINDOW *contentwin, WINDOW *miscwin) {
  

  // cleanup
  wclear(contentwin);
  box(contentwin, 0, 0);

  // static text
  mvwprintw(contentwin, 0, getmaxx(contentwin) / 2 - 3, "KNOB");
  curs_set(1);

  mvwprintw(contentwin, 3, 1, "Knob LEDs: ______");
  mvwprintw(contentwin, 3, 12, "______");
  mvwprintw(contentwin, 4, 1, "Possible Solutions:");
}
