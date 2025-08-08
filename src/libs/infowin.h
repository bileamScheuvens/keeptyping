#ifndef INFO_H
#define INFO_H

#include <ncurses.h>
#include <time.h>

struct Bombattrs {
  char serial_nr[6];
  int nr_batteries;
  int parallel_port;
  time_t timer;
};

void set_serial(struct Bombattrs* bombattrs);


WINDOW* create_infowin();
void refresh_infowin(WINDOW* infowin, struct Bombattrs* bombattrs);

#endif
