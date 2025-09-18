#include "button.h"


int get_valid_num(WINDOW* contentwin){
  while (1){
    int c = wgetch(contentwin);
    switch(c){
      case 27: //ESC
        return -1;
      default:
        c -= '0';
        if (c>9){ // ignore all non numeric
          continue;
        }
        return c;
    }
  }
}

bool hold_button(int color, int label, struct Bombattrs* bombattrs, WINDOW* contentwin){
  if (color == BLUE && label == ABORT){
    return true;
  }
  if (bombattrs->nr_batteries > 1 && label == DETONATE){
    return false;
  }
  if (color == WHITE && has_indicator(bombattrs, "CAR", true)){
    return true;
  }
  if (bombattrs->nr_batteries > 2 && has_indicator(bombattrs, "FRK", true)){
    return false;
  }
  if (color == YELLOW){
    return true;
  }
  if (label == HOLD){
    return false;
  }
  return true;
}

void button(WINDOW* contentwin, WINDOW* miscwin, struct Bombattrs* bombattrs){
  // cleanup 
  wclear(contentwin);
  box(contentwin,0,0);

  // reminder for dependencies
  char *msgs[] = {"Button relies on", "- Indicators", "- Battery count"};
  log_to_misc_many(miscwin, msgs, 3);

  // title and guide
  mvwprintw(contentwin, 0, getmaxx(contentwin)/2 - 3, "GLYPHS");
  mvwprintw(contentwin, 1, 1, "Select Color, then Label.");


  // TODO indicate whats currently being selected
  mvwprintw(contentwin, 2, 1, "(1)WHITE (2)BLACK    (3)BLUE (4)RED    (5)YELLOW");
  mvwprintw(contentwin, 3, 1, "(1)ABORT (2)DETONATE (3)HOLD (4)PRESS");

  // TODO indicate selections
  int color = get_valid_num(contentwin);
  if (color == -1){
    return;
  }
  int label = get_valid_num(contentwin);
  if (label == -1){
    return;
  }


  if (hold_button(color, label, bombattrs, contentwin)){
    mvwprintw(contentwin, 5, 5, "HOLD & RELEASE ON:");
    mvwprintw(contentwin, 6, 5, "- BLUE: 4");
    mvwprintw(contentwin, 7, 5, "- YELLOW: 5");
    mvwprintw(contentwin, 8, 5, "- OTHERWISE: 1");
  } else {
    mvwprintw(contentwin, 5, 5, "TAP & RELEASE");
  }




  wrefresh(contentwin);

}

