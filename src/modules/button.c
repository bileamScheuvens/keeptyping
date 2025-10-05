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


void draw_button_select(WINDOW* contentwin, int color, int label){
  /* Redraw guide with highlights */

  disable_text(contentwin, color != RED);
  mvwprintw(contentwin, 3, 5, "(r)ed");
  disable_text(contentwin, color != BLUE);
  mvwprintw(contentwin, 3, 12, "(b)lue");
  disable_text(contentwin, color != BLACK);
  mvwprintw(contentwin, 3, 20, "blac(k)");
  disable_text(contentwin, color != WHITE);
  mvwprintw(contentwin, 3, 29, "(w)hite");
  disable_text(contentwin, color != YELLOW);
  mvwprintw(contentwin, 3, 40, "(y)ellow");
  disable_text(contentwin, false);

  disable_text(contentwin, label != ABORT);
  mvwprintw(contentwin, 4, 5, "(1) ABORT");
  disable_text(contentwin, label != DETONATE);
  mvwprintw(contentwin, 4, 16, "(2) DETONATE");
  disable_text(contentwin, label != HOLD);
  mvwprintw(contentwin, 4, 30, "(3) HOLD");
  disable_text(contentwin, label != PRESS);
  mvwprintw(contentwin, 4, 40, "(4) PRESS");
  disable_text(contentwin, false);
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


  int color = -1;
  int label = -1;
  draw_button_select(contentwin, color, label);

  while (1){
    int c = wgetch(contentwin);
    switch(c) {
      case 27: // Escape
      case 'q':
        return;
      case 'r':
        color = RED;
        break;
      case 'b':
        color = BLUE;
        break;
      case 'k':
        color = BLACK;
        break;
      case 'w':
        color = WHITE;
        break;
      case 'y':
        color = YELLOW;
        break;
      case '1':
        label = ABORT;
        break;
      case '2':
        label = DETONATE;
        break;
      case '3':
        label = HOLD;
        break;
      case '4':
        label = PRESS;
        break;
    }

    draw_button_select(contentwin, color, label);

    if (color == -1 || label == -1){
      continue;
    }

    if (hold_button(color, label, bombattrs, contentwin)){
      mvwprintw(contentwin, 6, 5, "HOLD & RELEASE ON:");
      mvwprintw(contentwin, 7, 5, "- BLUE: 4");
      mvwprintw(contentwin, 8, 5, "- YELLOW: 5");
      mvwprintw(contentwin, 9, 5, "- OTHERWISE: 1");
    } else {
      mvwprintw(contentwin, 6, 5, "TAP & RELEASE     ");
      mvwprintw(contentwin, 7, 5, "         ");
      mvwprintw(contentwin, 8, 5, "           ");
      mvwprintw(contentwin, 9, 5, "              ");
    }
  }




  wrefresh(contentwin);

}

