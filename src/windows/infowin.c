#include "infowin.h"

bool odd_serial_nr(struct Bombattrs* bombattrs){
  for (int i=5; i>= 0; i--){
    char x = bombattrs->serial_nr[i];
    if (isdigit(x)){
      return x % 2 == 1;
    }
  }
  return -1;
}

int TITLE_LABEL;
int SERIAL_LABEL;
int SERIAL_CONTENT;
int BATTERY_LABEL;
int BATTERY_CONTENT;
int PORT_LABEL;
int PORT_CONTENT;
int TIMER_LABEL;
int TIMER_CONTENT;

WINDOW* create_infowin(){
  WINDOW* infowin = newwin(3,0,0,0);

  int winlen = getmaxx(infowin);
  TITLE_LABEL = winlen/2 - 5 ;
  SERIAL_LABEL = 1;
  SERIAL_CONTENT = SERIAL_LABEL + 13;
  BATTERY_LABEL = winlen/3;
  BATTERY_CONTENT = BATTERY_LABEL + 13;
  PORT_LABEL = 2*winlen/3;
  PORT_CONTENT = PORT_LABEL + 9;
  TIMER_LABEL = winlen-15;
  TIMER_CONTENT = TIMER_LABEL + 9;

  return infowin;
}


void refresh_infowin(WINDOW* infowin, struct Bombattrs* bombattrs){
  wclear(infowin);
  box(infowin,0,0);
  mvwprintw(infowin, 0, TITLE_LABEL, "INFO PANEL");

  // ----------------- SERIAL NUMBER ---------------------
  mvwprintw(infowin, 1, SERIAL_LABEL, "(S)erial Nr: ");
  if (bombattrs->serial_nr[0] != '-') {
    mvwprintw(infowin, 1, SERIAL_CONTENT, "%s", bombattrs->serial_nr);
  } else {
    mvwprintw(infowin, 1, SERIAL_CONTENT, "NULL");
  }
  // ------------------ NR BATTERIES ---------------------- 
  mvwprintw(infowin, 1, BATTERY_LABEL, "(B)atteries: ");
  if (bombattrs->nr_batteries) {
    mvwprintw(infowin, 1, BATTERY_CONTENT, "%d", bombattrs->nr_batteries-1);
  } else {
    mvwprintw(infowin, 1, BATTERY_CONTENT, "NULL");
  }
  // -------------------- PORTS ------------------------ 
  // TODO: support more than parallel
  mvwprintw(infowin, 1, PORT_LABEL, "(P)orts: ");
  switch (bombattrs->parallel_port) {
    case 1:
      mvwprintw(infowin, 1, PORT_CONTENT, "[Parallel]");
      break;
    case 0:
      mvwprintw(infowin, 1, PORT_CONTENT, "[]");
      break;
    default:
      mvwprintw(infowin, 1, PORT_CONTENT, "NULL");
  }
  // -------------------- TIMER ------------------------ 
  mvwprintw(infowin, 1, TIMER_LABEL, "(T)imer: ");
  if (bombattrs->timer) {
    // TODO manage start time
    mvwprintw(infowin, 1, TIMER_CONTENT, "%ld", bombattrs->timer%60);
  } else {
    mvwprintw(infowin, 1, TIMER_CONTENT, "NULL");
  }

  wrefresh(infowin);
}

void set_serial(WINDOW* infowin, struct Bombattrs* bombattrs){
  char serial_nr[6];
  mvwprintw(infowin, 1, SERIAL_CONTENT, "000000");
  wmove(infowin, 1, SERIAL_CONTENT);
  curs_set(1);
  wrefresh(infowin);
  for (int i = 0; i<6; i++){
    int c = wgetch(infowin);
    switch (c){
      case 10: // ENTER
      case 27: // Esc
        i = 6;
        break;
      case 127: // Backspace
        if (i>0){
          i-=2;
          wmove(infowin, 1, SERIAL_CONTENT+i+1);
        }
        break;
      case '_':
        if (i>1){
          i--;
        }
        break;
      default:
        c = c > 90 ? c-32 : c; // transform to uppercase
        mvwprintw(infowin, 1, SERIAL_CONTENT+i, "%c", c);
        bombattrs->serial_nr[i] = c;
        wrefresh(infowin);
    }
  }
  curs_set(0);
}

void set_batteries(WINDOW* infowin, struct Bombattrs* bombattrs){
  wmove(infowin, 1, BATTERY_CONTENT);
  curs_set(1);
  int c = wgetch(infowin);
  c -= '0';
  if (0<=c && c<=9){
    bombattrs->nr_batteries = c+1;
  }
  curs_set(0);
  refresh_infowin(infowin, bombattrs);
}

void set_port(WINDOW* infowin, struct Bombattrs* bombattrs){
  bombattrs->parallel_port = -1;
  refresh_infowin(infowin, bombattrs);
  mvwprintw(infowin, 1, PORT_CONTENT, "(y/n)");
  wrefresh(infowin);
  int c = wgetch(infowin);
  switch (c) {
    case 27:
      break;
    case 'y':
      bombattrs->parallel_port = 1;
      break;
    case 'n':
      bombattrs->parallel_port = 0;
      break;
  }
  refresh_infowin(infowin, bombattrs);
}


