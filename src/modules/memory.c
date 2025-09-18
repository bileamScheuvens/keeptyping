#include "memory.h"

struct StageResult {
  int val;
  bool is_pos;
};

struct StageResult resolve_stage(int stage, int displayed, int digits[], int positions[]){
  int val;
  bool is_pos;
  // TODO find some way to make this readable
  switch (stage){
    case 0:
      switch(displayed){
        case 1: 
        case 2:
          val = 2;
          is_pos = true;
          break;
        case 3:
          val = 3;
          is_pos = true;
          break;
        case 4:
          val = 4;
          is_pos = true;
          break;
      } break;
    case 1:
      switch(displayed){
        case 1: 
          val = 4;
          is_pos = false;
          break;
        case 2:
          val = positions[0];
          is_pos = true;
          break;
        case 3:
          val = 1;
          is_pos = true;
          break;
        case 4:
          val = 4;
          is_pos = false;
          break;
      } break;
    case 2:
      switch(displayed){
        case 1: 
          val = digits[1];
          is_pos = false;
          break;
        case 2:
          val = digits[0];
          is_pos = false;
          break;
        case 3:
          val = 3;
          is_pos = true;
          break;
        case 4:
          val = 4;
          is_pos = false;
          break;
      } break;
    case 3:
      switch(displayed){
        case 1: 
          val = positions[0];
          is_pos = true;
          break;
        case 2:
          val = 1;
          is_pos = true;
          break;
        case 3:
        case 4:
          val = positions[1];
          is_pos = true;
          break;
      } break;
    case 4:
      switch(displayed){
        case 1: 
          val = digits[0];
          is_pos = false;
          break;
        case 2:
          val = digits[1];
          is_pos = false;
          break;
        case 3:
          val = digits[3];
          is_pos = true;
          break;
        case 4:
          val = digits[2];
          is_pos = true;
          break;
      }
  }
  struct StageResult sr = {val, is_pos};
  return sr;
}

void memory_get_complement(WINDOW * contentwin, int given[], int other[], int GIVENX, int OTHERX, int BASEY, int stage, int val){
  /* Write given hint and get complement. 
   * Example: Click position 2 -> given: pos, other: digit, val: 2 
   */
  given[stage] = val;
  mvwprintw(contentwin, BASEY+stage, GIVENX, "%d", val);
  wmove(contentwin, BASEY+stage, OTHERX);

  // skip feedback for last stage
  if (stage == 4){ return; }
  int c = wgetch(contentwin);
  if (c == 27 || c == 'q'){ return; }
  c -= '0';
  other[stage] = c;
  mvwprintw(contentwin, BASEY+stage, OTHERX, "%d", c);
}

void memory(WINDOW* contentwin, WINDOW* miscwin){
  // cleanup 
  wclear(contentwin);
  box(contentwin,0,0);
  int digits[5];
  int positions[5];
  int BASEY = 7;
  int DIGX = 7;
  int POSX = 13;

  // title and guide
  mvwprintw(contentwin, 0, getmaxx(contentwin)/2 - 3, "MEMORY");
  mvwprintw(contentwin, 1, 1, "Input displayed number, then input complement to hint.");


  mvwprintw(contentwin, 2, 5, "-----------");
  mvwprintw(contentwin, 3, 5, "|    ?    |");
  mvwprintw(contentwin, 4, 5, "-----------");
  mvwprintw(contentwin, 5, 5, " DIG | POS ");
  mvwprintw(contentwin, 6, 5, "-----------");
  mvwprintw(contentwin, 7, 5, "     |     ");
  mvwprintw(contentwin, 8, 5, "     |     ");
  mvwprintw(contentwin, 9, 5, "     |     ");
  mvwprintw(contentwin, 10, 5, "     |     ");
  mvwprintw(contentwin, 11, 5, "     |     ");
  wrefresh(contentwin);

  curs_set(1);
  for (int stage=0; stage<5; stage++){
    // digit on display
    wmove(contentwin, 3, 10);
    int c = wgetch(contentwin);

    // break on q or ESC
    if (c == 27 || c == 'q'){ return; } 
    mvwprintw(contentwin, 3, 10, "%c", c);
    struct StageResult sr = resolve_stage(stage, c-'0', digits, positions);

    // if hint gives position, draw and wait for digit
    // TODO rewrite this with less redundancy
    if (sr.is_pos) {
      memory_get_complement(contentwin, positions, digits, POSX, DIGX, BASEY, stage, sr.val);
      // positions[stage] = sr.val;
      // mvwprintw(contentwin, BASEY+stage, POSX, "%d", sr.val);
      // wmove(contentwin, BASEY+stage, DIGX);
      //
      // if (stage == 5){ return; }
      // c = wgetch(contentwin);
      // if (c == 27 || c == 'q'){ return; }
      // c -= '0';
      // digits[stage] = c;
      // mvwprintw(contentwin, BASEY+stage, DIGX, "%d", c);
    } else { 
      memory_get_complement(contentwin, positions, digits, DIGX, POSX, BASEY, stage, sr.val);
      // else, draw and wait for position
      // digits[stage] = sr.val;
      // mvwprintw(contentwin, BASEY+stage, DIGX, "%d", sr.val);
      // wmove(contentwin, BASEY+stage, POSX);
      //
      // if (stage == 5){ return; }
      // c = wgetch(contentwin);
      // if (c == 27 || c == 'q'){ return; }
      // c -= '0';
      // positions[stage] = c;
      // mvwprintw(contentwin, BASEY+stage, POSX, "%d", c);
    }
  }

  curs_set(0);

  wrefresh(contentwin);

}

