#include <ncurses.h>
#include <stdbool.h>
#include "libs/infowin.h"
#include "libs/contentwin.h"



int main(){
  // init TUI
  initscr();
  cbreak();
  noecho();
  curs_set(0);
  
  // global bomb attributes
  WINDOW* infowin = create_infowin();
  struct Bombattrs bombattrs;

  refresh_infowin(infowin, &bombattrs);

  WINDOW* contentwin = create_contentwin();

  // main loop
  bool running = true;
  while (running) {
    int c = wgetch(contentwin);
    switch(c) {
      case 'q':
        running = false;
        break;
      case 'S':
        set_serial(infowin, &bombattrs);
        break;
      case 'P':
        set_port(infowin, &bombattrs);
        break;
      default:
        mvwprintw(contentwin,0,0, "%c, %d", c, c);
    }
  }

  endwin();
}
