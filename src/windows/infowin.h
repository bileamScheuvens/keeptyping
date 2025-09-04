#ifndef INFO_H
#define INFO_H

#include <ncursesw/ncurses.h>
#include <time.h>
#include <ctype.h>
#include <stdbool.h>
#include <string.h>

#define SERIAL_NR_LEN 6
#define MAX_PORTS 6
#define MAX_PORT_LEN 12
#define MAX_INDICATORS 11

struct Bombattrs {
  char serial_nr[SERIAL_NR_LEN];
  int nr_batteries;
  int mistakes;
  char ports[MAX_PORTS][MAX_PORT_LEN];
  char indicators[MAX_INDICATORS][4];
  bool indicator_lit[MAX_INDICATORS];
  time_t timer;
};

bool odd_serial_nr(struct Bombattrs* bombattrs);
bool serial_has_vowel(struct Bombattrs* bombattrs);
bool has_port(struct Bombattrs* bombattrs, char port[]);
bool has_indicator(struct Bombattrs* bombattrs, char port[], bool lit);

extern int TITLE_LABEL;
extern int SERIAL_LABEL;
extern int SERIAL_CONTENT;
extern int BATTERY_LABEL;
extern int BATTERY_CONTENT;
extern int MISTAKES_LABEL;
extern int MISTAKES_CONTENT;
extern int TIMER_LABEL;
extern int TIMER_CONTENT;
extern int PORT_LABEL;
extern int PORT_CONTENT;
extern int INDICATOR_LABEL;
extern int INDICATOR_CONTENT;

void set_serial(WINDOW* infowin, struct Bombattrs* bombattrs);
void set_batteries(WINDOW* infowin, struct Bombattrs* bombattrs);
void add_mistake(WINDOW* infowin, struct Bombattrs* bombattrs);
void add_port(WINDOW* infowin, WINDOW* contentwin, struct Bombattrs* bombattrs);
void add_indicator(WINDOW* infowin, WINDOW* contentwin, struct Bombattrs* bombattrs);


WINDOW* create_infowin();
void refresh_infowin(WINDOW* infowin, struct Bombattrs* bombattrs);

#endif
