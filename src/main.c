#include <ncursesw/ncurses.h>
#include <stdbool.h>
#include "windows/infowin.h"
#include "windows/contentwin.h"
#include "windows/selectwin.h"
#include "windows/miscwin.h"

#include "modules/wires.h"
#include "modules/glyphs.h"
#include "modules/button.h"


int main(){
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
  WINDOW* infowin = create_infowin();
  refresh_infowin(infowin, &bombattrs);
  WINDOW* contentwin = create_contentwin();
  WINDOW* miscwin = create_miscwin();
  WINDOW* selectwin = create_selectwin();
  refresh_selectwin(selectwin, false);



  // main loop
  bool running = true;
  while (running) {
    int c = wgetch(selectwin);
    int c2;

    char msg[36];
    sprintf(msg, "key pressed: %d - %c", c, c);
    log_to_misc(miscwin, msg);
    switch(c) {
      // debug
      case 'q':
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
        switch(c2){
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
        // GLYPHS
      case 'g':
        refresh_selectwin(selectwin, true);
        glyphs(contentwin, miscwin);
        refresh_selectwin(selectwin, false);
        break;
      default:
        break;
    }
  }

  endwin();
}
