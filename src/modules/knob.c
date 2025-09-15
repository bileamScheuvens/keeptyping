#include "stdio.h"
#include "string.h"
#include <ncursesw/ncurses.h>
#include <stdbool.h>



struct LedConfig {
  bool leds[12];
  char position[5];
};

const struct LedConfig configs[] = {
  {{false, false, true, false, true, true, true, true, true, true, false, true}, "Up"},
  {{true, false, true, false, true, false, false, true, true, false, true, true}, "Up"},
  {{false, true, true, false, false, true, true, true, true, true, false, true}, "Down"},
  {{true, false, true, false, true, false, false, true, false, false, false, true}, "Down"},
  {{false, false, false, false, true, false, true, false, false, true, true, true}, "Left"},
  {{false, false, false, false, true, false, false, false, false, true, true, false}, "Left"},
  {{true, false, true, true, true, true, true, true, true, false, true, false}, "Right"},
  {{true, false, true, true, false, false, true, true, true, false, true, false}, "Right"}
};

int cursor_position_x(int index) {
  return 13 + index % 6;
}

int cursor_position_y(int index) {
  return 3 + index / 6;
}

void knob(WINDOW *contentwin, WINDOW *miscwin) {
  

  // cleanup
  wclear(contentwin);
  box(contentwin, 0, 0);

  // static text
  mvwprintw(contentwin, 0, getmaxx(contentwin) / 2 - 3, "KNOB");
  curs_set(1);

  mvwprintw(contentwin, 3, 2, "Knob LEDs: ______");
  mvwprintw(contentwin, 4, 13, "______");
  mvwprintw(contentwin, 7, 2, "Knob Configuration:");
  

  bool input[13];
  for (int index = 0; index < 12; index++) {
    int x = cursor_position_x(index);
    int y = cursor_position_y(index);
    wmove(contentwin, y, x);
    int c = wgetch(contentwin);

    switch (c) {
      case 'q':
        return;
      case 'o':
        input[index] = true;
        waddch(contentwin, c);
        break;
      case 'x':
        input[index] = false;
        waddch(contentwin, c);
        break;
        // TODO: Case for delete/backspace
      default:
        index--;
    }
  }
  char position[3] = "Up";

  char* string;
  asprintf(string, "Knob Position: %s", position);
  mvwprintw(contentwin, 7, 2, string);
  wrefresh(contentwin);
  return;
}
