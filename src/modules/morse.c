#include "morse.h"
#include <ncursesw/ncurses.h>
#include <stdbool.h>

void morse(WINDOW *contentwin, WINDOW *miscwin) {

  // cleanup
  wclear(contentwin);
  box(contentwin, 0, 0);

  // title and guide
  mvwprintw(contentwin, 0, getmaxx(contentwin) / 2 - 3, "MORSE");
  curs_set(1);

  mvwprintw(contentwin, 2, 1, "Morse: ______________________________");
  wmove(contentwin, 2, 8);

  char morse_input[MAXLEN_MORSE];

  for (int i = 0; i < MAXLEN_MORSE; i++) {
    int c = wgetch(contentwin);
    if (c != '.' && c != '-' && c != ' ') {
      i--;
      continue;
    }
    waddch(contentwin, c);
    morse_input[i] = c;
  }
}
