#include <ncurses.h>
#include <string.h>
#include "infowin.h"


WINDOW* create_infowin(){
  WINDOW* infowin = newwin(3,0,0,0);

  box(infowin,0,0);
  wrefresh(infowin);

  // wgetch(infowin);
  return infowin;
}


void refresh_infowin(WINDOW* infowin, struct Bombattrs* bombattrs){
  int winlen = getmaxx(infowin);

  // serial number
  if (bombattrs->serial_nr[0] != '\0') {
    mvwprintw(infowin, 1, 1, "(S)erial Nr: %s", bombattrs->serial_nr);
  } else {
    mvwprintw(infowin, 1, 1, "(S)erial Nr: NULL");
  }
  // nr batteries
  if (bombattrs->nr_batteries) {
    mvwprintw(infowin, 1, winlen/3, "(B)atteries: %d", bombattrs->nr_batteries);
  } else {
    mvwprintw(infowin, 1, winlen/3, "(B)atteries: NULL");
  }
  // ports 
  // TODO: support more than parallel
  if (bombattrs->parallel_port) {
    mvwprintw(infowin, 1, 2*winlen/3, "(P)orts: [Parallel]");
  } else {
    mvwprintw(infowin, 1, 2*winlen/3, "(P)orts: NULL");
  }
  // timer
  if (bombattrs->timer) {
    // TODO manage start time
    mvwprintw(infowin, 1, winlen-15, "(T)imer: %ld", bombattrs->timer%60);
  } else {
    mvwprintw(infowin, 1, winlen-15, "(T)imer: NULL");
  }

  wrefresh(infowin);
}

void set_serial(struct Bombattrs* bombattrs){
  // TODO: open window to allow input
  char *serial_nr;
  strncpy(bombattrs->serial_nr, serial_nr, 6);
}
