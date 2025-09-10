#include "windows/contentwin.h"
#include "windows/infowin.h"
#include "windows/miscwin.h"
#include "windows/selectwin.h"
#include <ncursesw/ncurses.h>
#include <stdbool.h>

#include "modules/button.h"
#include "modules/glyphs.h"
#include "modules/memory.h"
#include "modules/morse.h"
#include "modules/simon_says.h"
#include "modules/wires.h"
#include "modules/password.h"

int main() {
  // init TUI
  initscr();
  cbreak();
  noecho();
  start_color();
  curs_set(0);

  // color pair 1 means disabled
  // use yellow for gray
  init_color(COLOR_YELLOW, 300, 300, 300);
  init_pair(1, COLOR_YELLOW, COLOR_BLACK);

  // global bomb attributes
  struct Bombattrs bombattrs = {0};
  bombattrs.nr_batteries = -1;
  bombattrs.mistakes = 0;
  bombattrs.serial_nr[0] = '-';

  // init windows
  WINDOW *infowin = create_infowin();
  refresh_infowin(infowin, &bombattrs);
  WINDOW *contentwin = create_contentwin();
  WINDOW *miscwin = create_miscwin();
  WINDOW *selectwin = create_selectwin();
  refresh_selectwin(selectwin, false);

  // main loop
  bool running = true;
  while (running) {
    int c = wgetch(selectwin);
    int c2;

    // debug
    char msg[36];
    sprintf(msg, "key pressed: %d - %c", c, c);
    log_to_misc(miscwin, msg);
    switch (c) {
    case 'q':
      // TODO warn about aborting
      running = false;
      break;
    case 'S':
      set_serial(infowin, &bombattrs);
      break;
    case 'M':
      add_mistake(infowin, &bombattrs);
      break;
    case 'B':
      set_batteries(infowin, &bombattrs);
      break;
    case 'P':
      add_port(infowin, contentwin, &bombattrs);
      break;
    case 'I':
      add_indicator(infowin, contentwin, &bombattrs);
      break;

    // WIRES
    case 'w':
      c2 = wgetch(contentwin);
      refresh_selectwin(selectwin, true);
      switch (c2) {
      // TODO Highlight partial match
      case 'r':
        wires_regular(contentwin, miscwin, &bombattrs);
        break;
      case 'c':
        wires_complex(contentwin, miscwin, &bombattrs);
        break;
      case 's':
        wire_sequence(contentwin, miscwin);
        break;
      default:
        break;
      }
      refresh_selectwin(selectwin, false);
      break;
    // Button
    case 'b':
      refresh_selectwin(selectwin, true);
      button(contentwin, miscwin, &bombattrs);
      refresh_selectwin(selectwin, false);
      break;
    // SIMON SAYS OR SIX DIRECTIONS
    case 's':
      c2 = wgetch(contentwin);
      refresh_selectwin(selectwin, true);
      switch (c2) {
      // TODO Highlight partial match
      case 'd':
        break;
      case 's':
        simon_says(contentwin, selectwin, &bombattrs);
        refresh_selectwin(selectwin, true);
        break;
      }
      break;
    // GLYPHS
    case 'g':
      refresh_selectwin(selectwin, true);
      glyphs(contentwin, miscwin);
      refresh_selectwin(selectwin, false);
      break;
    // MEMORY OR MORSE
    case 'm':
      c2 = wgetch(contentwin);
      refresh_selectwin(selectwin, true);
      switch (c2) {
      case 'e':
        memory(contentwin, miscwin);
        break;
      case 'o':
        morse(contentwin, miscwin);
        break;
      }
      refresh_selectwin(selectwin, false);
      break;
    // LABYRINTH
    case 'l':
      refresh_selectwin(selectwin, true);
      // labyrinth(contentwin, miscwin);
      refresh_selectwin(selectwin, false);
      break;

    // PASSWORD
    case 'p':
      refresh_selectwin(selectwin, true);
      password(contentwin, miscwin);
      refresh_selectwin(selectwin, false);

    default:
      break;
    }
  }

  endwin();
}
