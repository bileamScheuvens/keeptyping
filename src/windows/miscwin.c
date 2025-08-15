#include <ncursesw/ncurses.h>
#include "miscwin.h"


WINDOW* create_miscwin(){
  WINDOW* miscwin = newwin(0,31,18,0);

  box(miscwin,0,0);
  mvwprintw(miscwin,0,9, "MISCELLANEOUS");
  wrefresh(miscwin);

  return miscwin;
}

void log_to_misc(WINDOW* miscwin, char *content){
  wclear(miscwin);
  box(miscwin,0,0);
  mvwprintw(miscwin,0,9, "MISCELLANEOUS");
  mvwprintw(miscwin,1,1, "%s", content);
  wrefresh(miscwin);
}

void log_to_misc_many(WINDOW* miscwin, char *content[], int count){
  wclear(miscwin);
  box(miscwin,0,0);
  mvwprintw(miscwin,0,9, "MISCELLANEOUS");
  for (int i=0; i<count; i++){
    mvwprintw(miscwin,1+i,1, "%s", content[i]);
  }
  wrefresh(miscwin);
}
