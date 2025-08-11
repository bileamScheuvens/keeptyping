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



bool resolve_complex(bool red, bool blue, bool star, bool led, struct Bombattrs* bombattrs){
  bool C = true;
  bool D = true;
  bool S = !odd_serial_nr(bombattrs);
  bool P = bombattrs->parallel_port;
  bool B = bombattrs->nr_batteries >= 2;

  // interpret these as bitstr and access array
  // TODO pray i translated this correctly
  bool key[] = {
    C, // 0000 - white, no star, no led
    D, // 0001 - white, no star, led
    C, // 0010  
    B, // 0011
    S, // 0100
    P, // 0101 - blue, no star, led
    D, // 0110
    P, // 0111
    S, // 1000
    B, // 1001
    C, // 1010
    B, // 1011
    S, // 1100
    S, // 1101
    P, // 1110
    D, // 1111
  };
  int idx = red*8 + blue*4 + star*2 + led;
  return key[idx];
}


void set_bool_and_draw(WINDOW* contentwin, bool *complex_attr, int pos, bool target){
  /*
  Utility to set complex wire attr and draw state to contentwin.
  */
  *complex_attr = target;
  if (target){
    mvwprintw(contentwin, 2, pos, "X");
  }else{
    mvwprintw(contentwin, 2, pos, " ");
  }
}

void wires_complex(WINDOW* contentwin, WINDOW* miscwin, struct Bombattrs* bombattrs){
  char *msgs[] = {"Complex wires rely on", "- Serial Nr", "- Parallel Port", "- Battery count"};
  log_to_misc_many(miscwin, msgs, 4);

  const int REDX = 16;
  const int BLUEX = 28;
  const int STARX = 40;
  const int LEDX = 51;
  bool red = false;
  bool blue = false;
  bool star = false;
  bool led = false;
  bool cut = true;


  // title and guide
  mvwprintw(contentwin, 0, getmaxx(contentwin)/2 - 6, "COMPLEX WIRES");
  mvwprintw(contentwin, 1, 1, "Specify color, star and LED.");
  mvwprintw(contentwin, 2, 1, "Toggle: (r)ed [ ], (b)lue [ ], (s)tar [ ], (l)ed [ ] |  (c)lear  |");
  mvwprintw(contentwin, 7, 15, "CUT WIRE -> %b", cut);
  wrefresh(contentwin);

  while(1){
    int c = wgetch(contentwin);
    switch(c){
      case 'q':
      case 10: // ENTER
      case 27: // Escape
        return;
        break;
      case 'r':
        set_bool_and_draw(contentwin, &red, REDX, !red);
        break;
      case 'b': 
        set_bool_and_draw(contentwin, &blue, BLUEX, !blue);
        break;
      case 's':
        set_bool_and_draw(contentwin, &star, STARX, !star);
        break;
      case 'l':
        set_bool_and_draw(contentwin, &led, LEDX, !led);
        break;
      case 'c':
        set_bool_and_draw(contentwin, &red, REDX, false);
        set_bool_and_draw(contentwin, &blue, BLUEX, false);
        set_bool_and_draw(contentwin, &star, STARX, false);
        set_bool_and_draw(contentwin, &led, LEDX, false);
        break;
    }
    cut = resolve_complex(red, blue, star, led, bombattrs);
    mvwprintw(contentwin, 7, 15, "CUT WIRE -> %b", cut);
    wrefresh(contentwin);
  }
}

int resolve_sequential(int color, int dest, int seq_idx){
  /* Lookup tables for sequential wires. 
   * Colors are 0 - red, 1 - blue, 2 - black. 
   * Dest is 100 -> A, 10 -> B, 1 -> C.
   * 
   * Format is [seq_idx] = 1(leading one)101 -> cut if a or c*/

  if (seq_idx > 8){
    return -1;
  }

  int key[3][9] = {
    //red
    { 
      1001,
      1010,
      1100,
      1101,
      1010,
      1101,
      1111,
      1110,
      1010,
    },
    // blue
    { 
      1010,
      1101,
      1010,
      1100,
      1010,
      1011,
      1001,
      1101,
      1100,
    },
    // black
    { 
      1111,
      1101,
      1010,
      1101,
      1010,
      1011,
      1110,
      1001,
      1001,
    }
  };
  int raw_key = key[color][seq_idx];
  // extract digit
  return (raw_key / dest) % 10;
}


void wire_sequence(WINDOW* contentwin, WINDOW* miscwin){
  init_pair(2, COLOR_RED, COLOR_BLACK); // red on black
  init_pair(3, COLOR_BLUE, COLOR_BLACK); // blue on black

  int red_count = 0;
  int blue_count = 0;
  int black_count = 0;
  int cut;

  // cleanup 
  wclear(contentwin);
  box(contentwin,0,0);

  // title and guide
  mvwprintw(contentwin, 0, getmaxx(contentwin)/2 - 6, "WIRE SEQUENCE");
  mvwprintw(contentwin, 1, 1, "Specify color and destination:");
  mvwprintw(contentwin, 2, 5, "red     blue      black");
  wattron(contentwin, COLOR_PAIR(2));
  mvwprintw(contentwin, 3, 4, "A B C");
  wattron(contentwin, COLOR_PAIR(3));
  mvwprintw(contentwin, 3, 13, "A B C");
  wattroff(contentwin, COLOR_PAIR(3));
  mvwprintw(contentwin, 3, 23, "A B C");
  mvwprintw(contentwin, 4, 4, "a s d    f g h     j k l");
  wrefresh(contentwin);

  while (1){
    int c = wgetch(contentwin);
    switch(c){
      case 'q':
      case 10: // ENTER
      case 27: // Escape
        return;
        break;
      case 'a':
        cut = resolve_sequential(0, 100, red_count);
        red_count += 1;
        break;
      case 's':
        cut = resolve_sequential(0, 10, red_count);
        red_count += 1;
        break;
      case 'd':
        cut = resolve_sequential(0, 1, red_count);
        red_count += 1;
        break;
      case 'f':
        cut = resolve_sequential(1, 100, blue_count);
        blue_count += 1;
        break;
      case 'g':
        cut = resolve_sequential(1, 10, blue_count);
        blue_count += 1;
        break;
      case 'h':
        cut = resolve_sequential(1, 1, blue_count);
        blue_count += 1;
        break;
      case 'j':
        cut = resolve_sequential(2, 100, blue_count);
        black_count += 1;
        break;
      case 'k':
        cut = resolve_sequential(2, 10, blue_count);
        black_count += 1;
        break;
      case 'l':
        cut = resolve_sequential(2, 1, blue_count);
        black_count += 1;
        break;
    }
  mvwprintw(contentwin, 5, 1, "Count:");
  mvwprintw(contentwin, 6, 6, "%d", red_count);
  mvwprintw(contentwin, 6, 15, "%d", blue_count);
  mvwprintw(contentwin, 6, 25, "%d", black_count);
  mvwprintw(contentwin, 8, 15, "CUT WIRE -> %d   ", cut);
  if (cut<0){
    mvwprintw(contentwin, 8, 15, "INVALID SEQUENCE");
  }
  wrefresh(contentwin);
  }
}

