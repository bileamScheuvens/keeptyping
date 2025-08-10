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
  
  // global bomb attributes
  struct Bombattrs bombattrs;
  bombattrs.parallel_port = -1;
  bombattrs.serial_nr[0] = '-';

  // init windows
  WINDOW* infowin = create_infowin();
  WINDOW* contentwin = create_contentwin();
  WINDOW* miscwin = create_miscwin();
  WINDOW* selectwin = create_selectwin();


  wattron(infowin, A_BLINK);
  refresh_infowin(infowin, &bombattrs);



  // main loop
  bool running = true;
  while (running) {
    int c = wgetch(selectwin);

    int c2;
    mvwprintw(miscwin,1,1, "%c, %d pressed", c, c);
    wrefresh(miscwin);
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
        switch(wgetch(contentwin)){
          // TODO Highlight partial match
          case 'r':
            wires_regular(contentwin, miscwin);
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

        break;
      default:
        break;
    }
  }

  endwin();
}
