#ifndef INFO_H
#define INFO_H

#include <ncurses.h>
#include <time.h>
#include <stdbool.h>

struct Bombattrs {
  char serial_nr[6];
  int nr_batteries;
  int parallel_port;
  time_t timer;
};

extern int TITLE_LABEL;
extern int SERIAL_LABEL;
extern int SERIAL_CONTENT;
extern int BATTERY_LABEL;
extern int BATTERY_CONTENT;
extern int PORT_LABEL;
extern int PORT_CONTENT;
extern int TIMER_LABEL;
extern int TIMER_CONTENT;

void set_serial(WINDOW* infowin, struct Bombattrs* bombattrs);
void set_batteries(WINDOW* infowin, struct Bombattrs* bombattrs);
void set_port(WINDOW* infowin, struct Bombattrs* bombattrs);


WINDOW* create_infowin();
void refresh_infowin(WINDOW* infowin, struct Bombattrs* bombattrs);

#endif
