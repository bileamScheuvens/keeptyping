#include "wires.h"
#include "../windows/miscwin.h"

int count_wire_color(char wires[], int n_wires, char color){
  int res = 0;
  for (int i=0; i<n_wires; i++){
    res += wires[i] == color;
  }
  return res;
}

int resolve_3wire(char wires[]){  
  // if no red, cut second
  if (count_wire_color(wires, 3, 'r') == 0){
    return 2;
  }
  // if last is white, cut last
  if (wires[2] == 'w'){
    return 3;
  }
  // if more than 1 blue, cut last blue
  if (count_wire_color(wires, 3, 'b') > 1){
    return wires[2] == 'b' ? 3 : 2;
  }
  // otherwise cut last
  return 3;
}

int resolve_4wire(char wires[], struct Bombattrs* bombattrs){
  // if more than one red wire and odd serial, cut last red
  if (count_wire_color(wires, 4, 'r') > 1 && odd_serial_nr(bombattrs)){
    if (wires[3] == 'r'){
      return 4;
    }
    return wires[2] == 'r' ? 3 : 2;
  }
  // if last is yellow and no red cut first
  if (wires[3] == 'y' && count_wire_color(wires, 4, 'r') == 0){
    return 1;
  }
  // if one blue, cut first
  if (count_wire_color(wires, 4, 'b') == 1){
    return 1;
  }
  // if more than one yellow, cut last
  if (count_wire_color(wires, 4, 'y') > 1){
    return 4;
  }
  // otherwise cut seconds
  return 2;
}

int resolve_5wire(char wires[], struct Bombattrs* bombattrs){
  // if last black and odd serial, cut 4
  if (wires[4] == 'k' && odd_serial_nr(bombattrs)){
    return 4;
  }
  // if one red and more than one yellow, cut first
  if (count_wire_color(wires, 5, 'r') == 1 && count_wire_color(wires, 5, 'y') > 1){
    return 1;
  }
  // if no black, cut seconds
  if (count_wire_color(wires, 5, 'k') == 0){
    return 2;
  }
  // otherwise cut first
  return 1;
}
int resolve_6wire(char wires[], struct Bombattrs* bombattrs){
  // if no yellow and odd serial, cut third
  if (count_wire_color(wires, 6, 'y') == 0 && odd_serial_nr(bombattrs)){
    return 3;
  }
  // if one yellow and more than one white, cut fourth
  if (count_wire_color(wires, 6, 'y') == 1 && count_wire_color(wires, 6, 'w') > 1){
    return 4;
  }
  // if no red, cut last
  if (count_wire_color(wires, 6, 'r') == 0){
    return 6;
  }
  // otherwise cut fourth
  return 4;
}

void wires_regular(WINDOW* contentwin, WINDOW* miscwin, struct Bombattrs* bombattrs){
  char wires[6];
  int n_wires = 6;

  // reminder for serial number
  log_to_misc(miscwin, "Wires rely on Serial Nr!");

  // title and guide
  mvwprintw(contentwin, 0, getmaxx(contentwin)/2 - 6, "REGULAR WIRES");
  mvwprintw(contentwin, 1, 1, "Input Wire colors, press enter when done.");
  mvwprintw(contentwin, 2, 1, "Color guide: (r)ed, (b)lue, (y)ellow, (w)hite, blac(k)");
  mvwprintw(contentwin, 4, 1, "Wires: ______");
  wmove(contentwin, 4,8);
  wrefresh(contentwin);
  curs_set(1);

  // Collect wire sequence
  for (int i=0; i<6; i++){
    int c = wgetch(contentwin);
    switch (c){
      case 'r':
      case 'b':
      case 'y':
      case 'w':
      case 'k':
        wires[i] = c;
        mvwprintw(contentwin, 4, 8+i, "%c", c);
        break;
      case 10: // ENTER
      case 27: // Escape
        n_wires = i;
        i = 6;
        break;
      case 127: // Backspace
        if (i>1){
          i-=2;
          wmove(contentwin, 4, 8+i+1);
          wrefresh(contentwin);
        }
        break;
      default:
        i--;
        char msg[60];
        sprintf(msg, "Invalid Key: %d - %c", c, c);
        log_to_misc(miscwin, msg);
        break;
    }
    wrefresh(contentwin);
  }

  if (n_wires < 3){
    char msg[60];
    sprintf(msg, "Invalid, too few wires: %d", n_wires);
    log_to_misc(miscwin, msg);
    wclear(contentwin);
    box(contentwin, 0,0);
    wrefresh(contentwin);
    return;
  }

  // ---------- DISPATCH WIRE SOLVER ---------- 
  int result;
  switch(n_wires){
    case 3:
      result = resolve_3wire(wires);
      break;
    case 4:
      result = resolve_4wire(wires, bombattrs);
      break;
    case 5:
      result = resolve_5wire(wires, bombattrs);
      break;
    case 6:
      result = resolve_6wire(wires, bombattrs);
      break;
  }


  mvwprintw(contentwin, 7, 15, "CUT WIRE %d", result);
  wrefresh(contentwin);
  curs_set(0);
}



void wires_complex(WINDOW* contentwin, WINDOW* miscwin){
  mvwprintw(miscwin, 2, 1, "complex selected");
  wrefresh(miscwin);
}

void wires_sequence(WINDOW* contentwin, WINDOW* miscwin){
  mvwprintw(miscwin, 2, 1, "sequence selected");
  wrefresh(miscwin);
}

