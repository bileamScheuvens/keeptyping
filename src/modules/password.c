#include "password.h"

const char *passwords[35] = {
  "about",
  "after",
  "again",
  "below",
  "could",
  "every",
  "first",
  "found",
  "great",
  "house",
  "large",
  "learn",
  "never",
  "other",
  "place",
  "plant",
  "point",
  "right",
  "small",
  "sound",
  "spell",
  "still",
  "study",
  "their",
  "there",
  "these",
  "thing",
  "think",
  "three",
  "water",
  "where",
  "which",
  "world",
  "would",
  "write",
};

int y_to_inputpos(int y){ return 4 + y; };
int x_to_inputpos(int x){ return 3 + 2*x; };

int y_to_wordpos(int y){ return 4 + 2*y; };
int x_to_wordpos(int x){ return 15 + 7*x; };

bool is_in_letters(char x, char letters[6]){
  for (int i=0; i<6; i++){
    if (x == letters[i]){ return true; };
  }
  return false;
}

void draw_word(WINDOW* contentwin, int y, int x, char letters[5][6], const char *word){
  for (int i=0; i<5; i++){
    int c = word[i];
    // check whether all possibilities for this slot have been entered
    bool slot_complete = letters[i][5] != '_';
    bool is_present = is_in_letters(c, letters[i]);
    // if letter not possible despite all possibilities entered, skip word
    if (slot_complete && !is_present){
        mvwprintw(contentwin, y, x, "      ");
        return;
    }

    // otherwise print char colored by whether its present
    disable_text(contentwin, !is_present);
    
    mvwaddch(contentwin, y, x+i, c);
    wattron(contentwin, COLOR_PAIR(PAIR_REGULAR));
  }
}

void refresh_word_grid(WINDOW* contentwin, char letters[5][6]){
  for (int x=0; x<5; x++){
    for (int y=0; y<7; y++){
      draw_word(contentwin, y_to_wordpos(y), x_to_wordpos(x), letters, passwords[5*y+x]);
      // mvwprintw(contentwin, y_to_wordpos(y), x_to_wordpos(x), "%s", passwords[5*y+x]);
    };
  };
}

void password(WINDOW* contentwin, WINDOW* miscwin){
  // [position][possibilities]
  char letters[5][6];
  memset(letters, '_', 30);

  // cleanup 
  wclear(contentwin);
  box(contentwin,0,0);

  // title and guide
  mvwprintw(contentwin, 0, getmaxx(contentwin)/2 - 4, "PASSWORD");
  mvwprintw(contentwin, 1, 1, "Add letters until one possible password remains.");
  mvwprintw(contentwin, 2, 1, "Escape or Backspace to quit.");


  // draw suggestion grid
  for (int x=0; x<5; x++){
    for (int y=0; y<6; y++){
      mvwaddch(contentwin, y_to_inputpos(y), x_to_inputpos(x), letters[x][y]);
    };
  };


  curs_set(1);
  int c;
  // gather input
  for (int x=0; x<5; x++){
    for (int y=0; y<6; y++){
      int y_print = y_to_inputpos(y);
      int x_print = x_to_inputpos(x);
      refresh_word_grid(contentwin, letters);
      wmove(contentwin, y_print, x_print);
      c = wgetch(contentwin);
      switch(c){
        case 127: // BACKSPACE
        case 27: // ESCAPE
          return;
        // TODO navigation
        default:
          letters[x][y] = c;
          mvwaddch(contentwin, y_print, x_print, c);
          break;
      }
    };

  };
  curs_set(0);
  // wrefresh(contentwin);
}

