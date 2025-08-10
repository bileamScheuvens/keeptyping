#include "selectwin.h"


WINDOW* create_selectwin(){
  WINDOW* selectwin = newwin(13,31,3,0);
  return selectwin;
}

void refresh_selectwin(WINDOW* selectwin, bool disabled){
  // TODO highlight selected option
  box(selectwin, 0,0);

  mvwprintw(selectwin, 0, 7, "MODULE SELECTION");
  if (disabled){
    wattron(selectwin, COLOR_PAIR(1));
  }
  mvwprintw(selectwin, 1, 1, "- (w)ires -+-- (r)egular");
  mvwprintw(selectwin, 2, 1, "-          +-- (c)omplicated");
  mvwprintw(selectwin, 3, 1, "-          \\-- (s)equences");
  mvwprintw(selectwin, 4, 1, "- (b)utton");
  mvwprintw(selectwin, 5, 1, "- (s)imon (s)ays");
  mvwprintw(selectwin, 6, 1, "- (s)ix (d)irections");
  mvwprintw(selectwin, 7, 1, "- (me)mory");
  mvwprintw(selectwin, 8, 1, "- (mo)rse code");
  mvwprintw(selectwin, 9, 1, "- (l)abyrinth");
  mvwprintw(selectwin, 10, 1, "- (p)assword");
  mvwprintw(selectwin, 11, 1, "- (k)nob");
  wrefresh(selectwin);
  wattroff(selectwin, COLOR_PAIR(1));
}
