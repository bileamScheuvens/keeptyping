#include <ncurses.h>
#include <stdbool.h>
#include "windows/infowin.h"
#include "windows/contentwin.h"
#include "windows/selectwin.h"
#include "windows/miscwin.h"

#include "modules/wires.h"


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
  struct Bombattrs bombattrs;
  bombattrs.parallel_port = -1;
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
      case 'B':
        set_batteries(infowin, &bombattrs);
        break;
      case 'P':
        set_port(infowin, &bombattrs);
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
            wires_complex(contentwin, miscwin);
            break;
          case 's':
            wires_sequence(contentwin, miscwin);
            break;
          default:
            break;
        }
        refresh_selectwin(selectwin, false);
        break;
      default:
        break;
    }
  }

  endwin();
}
