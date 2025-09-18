#include "six_directions.h"

const char *stage_1_key[28] = {
  "         B L",
  "BLANK    M R",
  "C        T R",
  "CEE      B R",
  "DISPLAY  B R",
  "FIRST    T R",
  "HOLD ON  B R",
  "LEAD     B R",
  "LED      M L",
  "LEED     B L",
  "NO       B R",
  "NOTHING  M L",
  "OKAY     T R",
  "READ     M R",
  "RED      M R",
  "REED     B L",
  "SAYS     B R",
  "SEE      B R",
  "THEIR    M R",
  "THERE    B R",
  "THEY ARE M L",
  "THEY'RE  B L",
  "UR       T L",
  "YES      M L",
  "YOU      M R",
  "YOU ARE  B R",
  "YOU'RE   M R",
  "YOUR     M R",
};

const char *stage_2_key[28] = {
  "BLANK ",
  "DONE ",
  "FIRST ",
  "HOLD ",
  "LEFT ",
  "LIKE ",
  "MIDDLE ",
  "NEXT ",
  "NO ",
  "NOTHING ",
  "OKAY ",
  "PRESS ",
  "READ ",
  "RIGHT ",
  "SURE ",
  "U ",
  "UH HUH ",
  "UH UH ",
  "UHHH ",
  "UR ",
  "WAIT ",
  "WHAT ",
  "WHAT? ",
  "YES ",
  "YOU ARE ",
  "YOU ",
  "YOUR ",
  "YOU'RE ",
};

const char *stage_2_val[28] = {
  "WAIT, RIGHT, OKAY, MIDDLE, BLANK",
  "SURE, UH HUH, NEXT, WHAT?, YOUR, UR, YOU'RE, HOLD, LIKE, YOU, U, YOU ARE, UH UH, DONE",
  "LEFT, OKAY, YES, MIDDLE, NO, RIGHT, NOTHING, UHHH, WAIT, READY, BLANK, WHAT, PRESS, FIRST",
  "YOU ARE, U, DONE, UH UH, YOU, UR, SURE, WHAT?, YOU'RE, NEXT, HOLD",
  "RIGHT, LEFT",
  "YOU'RE, NEXT, U, UR, HOLD, DONE, UH UH, WHAT?, UH HUH, YOU, LIKE",
  "BLANK, READY, OKAY, WHAT, NOTHING, PRESS, NO, WAIT, LEFT, MIDDLE",
  "WHAT?, UH HUH, UH UH, YOUR, HOLD, SURE, NEXT",
  "BLANK, UHHH, WAIT, FIRST, WHAT, READY, RIGHT, YES, NOTHING, LEFT, PRESS, OKAY, NO",
  "UHHH, RIGHT, OKAY, MIDDLE, YES, BLANK, NO, PRESS, LEFT, WHAT, WAIT, FIRST, NOTHING",
  "MIDDLE, NO, FIRST, YES, UHHH, NOTHING, WAIT, OKAY",
  "RIGHT, MIDDLE, YES, READY, PRESS",
  "YES, OKAY, WHAT, MIDDLE, LEFT, PRESS, RIGHT, BLANK, READY",
  "YES, NOTHING, READY, PRESS, NO, WAIT, WHAT, RIGHT",
  "YOU ARE, DONE, LIKE, YOU'RE, YOU, HOLD, UH HUH, UR, SURE",
  "UH HUH, SURE, NEXT, WHAT?, YOU'RE, UR, UH UH, DONE, U",
  "UH HUH",
  "UR, U, YOU ARE, YOU'RE, NEXT, UH UH",
  "READY, NOTHING, LEFT, WHAT, OKAY, YES, RIGHT, NO, PRESS, BLANK, UHHH",
  "DONE, U, UR",
  "UHHH, NO, BLANK, OKAY, YES, LEFT, FIRST, PRESS, WHAT, WAIT",
  "UHHH, WHAT",
  "YOU, HOLD, YOU'RE, YOUR, U, DONE, UH UH, LIKE, YOU ARE, UH HUH, UR, NEXT, WHAT?",
  "OKAY, RIGHT, UHHH, MIDDLE, FIRST, WHAT, PRESS, READY, NOTHING, YES",
  "YOUR, NEXT, LIKE, UH HUH, WHAT?, DONE, UH UH, HOLD, YOU, U, YOU'RE, SURE, UR, YOU ARE",
  "SURE, YOU ARE, YOUR, YOU'RE, NEXT, UH HUH, UR, HOLD, WHAT?, YOU",
  "UH UH, YOU ARE, UH HUH, YOUR",
  "YOU, YOU'RE",
};


bool word_possible(const char *word, char letters[8]){
  for (int i=0; i<8; i++){
    if (letters[i] == '_') return true; 
    if (word[i] != letters[i]) return false; 
  }
  return true;
}

void draw_remaining_options(WINDOW* contentwin, const char *options[28], char letters[8]){
  for (int i=0; i<28; i++){
    mvwprintw(contentwin, 3+i%13, 25+15*(i>13), "             ");
    if (!word_possible(options[i], letters)) continue;
    mvwprintw(contentwin, 3+i%13, 25+15*(i>13), "%s", options[i]);
  }
}

void draw_last_solution(WINDOW* contentwin, const char *options[28], const char *values[28], char letters[8]){
  bool has_solution = false;
  const char *solution = "";

  wmove(contentwin, 17, 1);
  wclrtoeol(contentwin);
  for (int i=0; i<28; i++){
    if (word_possible(options[i], letters)){
      // if second solution encountered, terminate
      if (has_solution) return;
      has_solution = true;
      solution = values[i];
    }
  }
  if (strcmp(solution, "") == 0) return;
  mvwprintw(contentwin, 17, 1, "Order: %s", solution);
}

void six_directions(WINDOW* contentwin, WINDOW* miscwin){
  // cleanup
  wclear(contentwin);
  box(contentwin,0,0);

  // title
  mvwprintw(contentwin, 0, getmaxx(contentwin)/2 - 7, "SIX DIRECTIONS");


  bool is_stage_2 = false;

  char letters[8];
  memset(letters, '_', 8);

  curs_set(1);  

  int c;
  // gather input
  for (int i=0; i<8; i++){
    mvwprintw(contentwin, 1, 1, "STAGE: %d", 1 + is_stage_2);
    // input prompt
    mvwprintw(contentwin, 3, 1, "Displayed: %s", letters);
    // filtered result
    if (is_stage_2){
      draw_remaining_options(contentwin, stage_2_key, letters);
      draw_last_solution(contentwin, stage_2_key, stage_2_val, letters);
    } else {
      draw_remaining_options(contentwin, stage_1_key, letters);
    }

    wmove(contentwin, 3, 12+i);
    c = wgetch(contentwin);
    switch(c){
      case 127: // BACKSPACE
        letters[i-1] = '_';
        i -= 2;
        i = i<0 ? -1 : i;
        break;
      case 23: // CTRL-W
        memset(letters, '_', 8);
        i = -1;
        break;
      case 27: // ESCAPE
      case 10: // ENTER
        return;
      case 9: // TAB
        // switch stage
        is_stage_2 = !is_stage_2;
        i = -1;
        memset(letters, '_', 8);
        break;
      default:
        c = c > 90 ? c-32 : c; // transform to uppercase
        letters[i] = c;
        break;
    }
  }
  curs_set(0);
}

