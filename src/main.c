#include <ncurses.h>
#include <string.h>
#include "libs/infowin.h"



int main(){
  // init TUI
  initscr();
  cbreak();
  noecho();
  
  // global bomb attributes
  WINDOW* infowin = create_infowin();
  struct Bombattrs bombattrs;

  refresh_infowin(infowin, &bombattrs);

  wgetch(infowin);

  endwin();
}
