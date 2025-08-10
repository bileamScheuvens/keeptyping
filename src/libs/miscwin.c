#include <ncurses.h>
#include "miscwin.h"


WINDOW* create_miscwin(){
  WINDOW* miscwin = newwin(0,31,16,0);

  box(miscwin,0,0);
  mvwprintw(miscwin,0,9, "MISCELLANEOUS");
  wrefresh(miscwin);

  return miscwin;
}

