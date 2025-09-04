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

bool serial_has_vowel(struct Bombattrs* bombattrs){
  for (int i=0; i<= 5; i++){
    char x = bombattrs->serial_nr[i];
    if (x == 'A' || x == 'E' || x == 'I' || x == 'O' || x == 'U'){
      return 1;
    }
  }
  return 0;
}


bool has_port(struct Bombattrs* bombattrs, char port[]){
  for (int i=0; i<MAX_PORTS; i++){
    if (strcmp(bombattrs->ports[i], port)){
      return true;
    }
  }
  return false;
}

bool has_indicator(struct Bombattrs* bombattrs, char indicator[], bool lit){
  for (int i=0; i<MAX_INDICATORS; i++){
    if (strcmp(bombattrs->indicators[i], indicator)){
      return bombattrs->indicator_lit[i];
    }
  }
  return false;
}

int TITLE_LABEL;
int SERIAL_LABEL;
int SERIAL_CONTENT;
int BATTERY_LABEL;
int BATTERY_CONTENT;
int MISTAKES_LABEL;
int MISTAKES_CONTENT;
int TIMER_LABEL;
int TIMER_CONTENT;
int PORT_LABEL;
int PORT_CONTENT;
int INDICATOR_LABEL;
int INDICATOR_CONTENT;

WINDOW* create_infowin(){
  WINDOW* infowin = newwin(4,0,0,0);

  int winlen = getmaxx(infowin);
  TITLE_LABEL = winlen/2 - 5 ;
  SERIAL_LABEL = 1;
  SERIAL_CONTENT = SERIAL_LABEL + 13;
  BATTERY_LABEL = winlen/3;
  BATTERY_CONTENT = BATTERY_LABEL + 13;
  MISTAKES_LABEL = 2*winlen/3;
  MISTAKES_CONTENT = MISTAKES_LABEL + 12;
  TIMER_LABEL = winlen-15;
  TIMER_CONTENT = TIMER_LABEL + 9;

  // second row
  PORT_LABEL = 1;
  PORT_CONTENT = PORT_LABEL + 9;
  INDICATOR_LABEL = winlen/2;
  INDICATOR_CONTENT = INDICATOR_LABEL + 15;

  return infowin;
}


void refresh_infowin(WINDOW* infowin, struct Bombattrs* bombattrs){
  wclear(infowin);
  box(infowin,0,0);
  mvwprintw(infowin, 0, TITLE_LABEL, "INFO PANEL");

  // ---------------- SERIAL NUMBER --------------------
  mvwprintw(infowin, 1, SERIAL_LABEL, "(S)erial Nr:");
  if (bombattrs->serial_nr[0] != '-') {
    mvwprintw(infowin, 1, SERIAL_CONTENT, "%s", bombattrs->serial_nr);
  } else {
    mvwprintw(infowin, 1, SERIAL_CONTENT, "NULL");
  }
  // ----------------- NR BATTERIES ---------------------
  mvwprintw(infowin, 1, BATTERY_LABEL, "(B)atteries:");
  if (bombattrs->nr_batteries >=0) {
    mvwprintw(infowin, 1, BATTERY_CONTENT, "%d", bombattrs->nr_batteries-1);
  } else {
    mvwprintw(infowin, 1, BATTERY_CONTENT, "NULL");
  }
  // ------------------- MISTAKES ----------------------- 
  mvwprintw(infowin, 1, MISTAKES_LABEL, "(M)istakes:");
  for (int i=0; i<bombattrs->mistakes; i++){
    mvwprintw(infowin, 1, MISTAKES_CONTENT+i, "X");
  }
  // -------------------- TIMER ------------------------ 
  mvwprintw(infowin, 1, TIMER_LABEL, "(T)imer:");
  if (bombattrs->timer) {
    // TODO manage start time
    mvwprintw(infowin, 1, TIMER_CONTENT, "%ld", bombattrs->timer%60);
  } else {
    mvwprintw(infowin, 1, TIMER_CONTENT, "NULL");
  }

  // -------------------- PORTS ------------------------ 
  mvwprintw(infowin, 2, PORT_LABEL, "(P)orts:");
  wmove(infowin, 2, PORT_CONTENT);
  for (int i=0; i<MAX_PORTS; i++){
    if (bombattrs->ports[i] == NULL){
      continue;
    }
    curs_set(0);
    waddstr(infowin, bombattrs->ports[i]);
    waddch(infowin, ' ');
  }
  
  // ------------------ INDICATORS ----------------------
  mvwprintw(infowin, 2, INDICATOR_LABEL, "(I)indicators:");
  wmove(infowin, 2, INDICATOR_CONTENT);
  for (int i=0; i<MAX_INDICATORS; i++){
    if (bombattrs->indicators[i][0] == '\0'){
      continue;
    }
    if (!bombattrs->indicator_lit[i]){
      wattron(infowin, COLOR_PAIR(1));
    }
    waddstr(infowin, bombattrs->indicators[i]);
    waddch(infowin, ' ');
    wattroff(infowin, COLOR_PAIR(1));
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

void add_mistake(WINDOW* infowin, struct Bombattrs* bombattrs){
  bombattrs->mistakes += 1;
  refresh_infowin(infowin, bombattrs);
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

void add_port(WINDOW* infowin, WINDOW* contentwin, struct Bombattrs* bombattrs){
  // cleanup 
  wclear(contentwin);
  box(contentwin,0,0);

  int half_width = getmaxx(contentwin)/2;
  // title 
  mvwprintw(contentwin, 0, half_width/2 - 7, "PORT SELECTION");

  // TODO ASCII art for ports
  // TODO make toggleable
  mvwprintw(contentwin, 2, 1, "(1) DVI-D");
  mvwprintw(contentwin, 5, 1, "(2) PARALLEL");
  mvwprintw(contentwin, 8, 1, "(3) PS/2");
  mvwprintw(contentwin, 2, half_width, "(4) RJ-45");
  mvwprintw(contentwin, 5, half_width, "(5) SERIAL");
  mvwprintw(contentwin, 8, half_width, "(6) STEREO RCA");

  while(1){
    int c = wgetch(contentwin);
    switch(c){
      case 'q':
      case 10: // ENTER
      case 27: // Escape
        return;
        break;
      case '1':
        strcpy(bombattrs->ports[0], "DVI-D");
        break;
      case '2':
        strcpy(bombattrs->ports[1], "PARALLEL");
        break;
      case '3':
        strcpy(bombattrs->ports[2], "PS/2");
        break;
      case '4':
        strcpy(bombattrs->ports[3], "RJ-45");
        break;
      case '5':
        strcpy(bombattrs->ports[4], "SERIAL");
        break;
      case '6':
        strcpy(bombattrs->ports[5], "STEREO RCA");
        break;
    }
  refresh_infowin(infowin, bombattrs);
  }
}


void add_indicator(WINDOW* infowin, WINDOW* contentwin, struct Bombattrs* bombattrs){
  // cleanup 
  wclear(contentwin);
  box(contentwin,0,0);

  char indicator[4];
  bool is_lit = true;
  int NEW_ID_CONTENT = 12;
  int LIT_POS = 7;

  int half_width = getmaxx(contentwin)/2;
  // title and guide
  mvwprintw(contentwin, 0, half_width/2 - 6, "ADD INDICATOR");
  mvwprintw(contentwin, 2, 1, "Indicator: ___");
  mvwprintw(contentwin, 3, 1, "Lit: [X] (tab)");

  curs_set(1);
  wmove(contentwin, 2, NEW_ID_CONTENT);
  wrefresh(contentwin);

  for (int i = 0; i<10; i++){
    int c = wgetch(infowin);
    switch (c){
      case 10: // ENTER
      case 27: // ESC
        i = 10;
        break;
      case 9: // TAB
        if (!is_lit){
          mvwprintw(contentwin, 3, LIT_POS, "X");
        } else {
          mvwprintw(contentwin, 3, LIT_POS, " ");
        }
        is_lit = !is_lit;
        i -= 1;
        wmove(contentwin, 2, SERIAL_CONTENT+i-1);
        break;
      case 127: // BACKSPACE
        if (i>0){
          i-=2;
          wmove(contentwin, 2, SERIAL_CONTENT+i-1);
        }
        break;
      case '_': // forgot why i did this
        if (i>1){
          i--;
        }
        break;
      default:
        // check within bounds
        if (i>=3){
          curs_set(0);
          break;
        }
        c = c > 90 ? c-32 : c; // transform to uppercase
        mvwprintw(contentwin, 2, NEW_ID_CONTENT+i, "%c", c);
        indicator[i] = c;
    }
    wrefresh(contentwin);
  }
  curs_set(0);

  // add to first empty indicator slot
  for (int i=0; i<MAX_INDICATORS; i++){
    if (bombattrs->indicators[i][0] == '\0'){
      strcpy(bombattrs->indicators[i], indicator);
      bombattrs->indicator_lit[i] = is_lit;
      refresh_infowin(infowin, bombattrs);
      return;
    }
  }
}
