#include "simon_says.h"


// Layout: [has vowel] [nr of strikes] [red blue green yellow]
char simon_lookup[2][3][32] = {
  // no vowel
  {
    " Blue   Yellow   Green    Red",
    " Red     Blue   Yellow  Green",
    "Yellow   Green   Blue     Red",
  },
  // vowel
  {
    " Blue    Red    Yellow  Green",
    "Yellow  Green    Blue     Red",
    "Green    Red    Yellow   Blue",
  }
};



void simon_says(WINDOW* contentwin, WINDOW* miscwin, struct Bombattrs* bombattrs){
  // cleanup 
  wclear(contentwin);
  box(contentwin,0,0);

  // reminder for dependencies
  char *msgs[] = {"Simon says relies on", "- Serial Nr", "- Nr of mistakes"};
  log_to_misc_many(miscwin, msgs, 3);

  // title and guide
  mvwprintw(contentwin, 0, getmaxx(contentwin)/2 - 5, "SIMON SAYS");

  mvwprintw(contentwin, 3, 3, "Flashing: Red   Blue    Green   Yellow");
  mvwprintw(contentwin, 4, 3, "           |      |       |        |");
  mvwprintw(contentwin, 5, 3, "           V      V       V        V");
  mvwprintw(contentwin, 6, 3, "Press:");
  
  char *row = simon_lookup[serial_has_vowel(bombattrs)][bombattrs->mistakes];
  mvwprintw(contentwin, 6, 11, "%s", row);

  wrefresh(contentwin);

}

