#include <ncurses.h>
#include "contentwin.h"


WINDOW* create_contentwin(){
  WINDOW* contentwin = newwin(0,0,3,0);

  box(contentwin,0,0);
  wrefresh(contentwin);

  return contentwin;
}


