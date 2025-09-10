#include "morse.h"
#include <assert.h>
#include <ncursesw/ncurses.h>
#include <stdbool.h>
#include <string.h>

const char *frequencies[16] = {
    "3.505", "3.515", "3.522", "3.532", "3.535", "3.542", "3.545", "3.552",
    "3.555", "3.565", "3.572", "3.575", "3.582", "3.592", "3.595", "3.600"};

const char *codes[16] = {
    "... .... . .-.. .-..", ".... .- .-.. .-.. ...", "... .-.. .. -.-. -.-",
    "- .-. .. -.-. -.-",    "-... --- -..- . ...",   ".-.. . .- -.- ...",
    "... - .-. --- -... .", "-... .. ... - .-. ---", "..-. .-.. .. -.-. -.-",
    "-... --- -- -... ...", "-... .-. . .- -.-",     "-... .-. .. -.-. -.-",
    "... - . .- -.-",       "... - .. -. --.",       "...- . -.-. - --- .-.",
    "-... . .- - ..."};

bool is_substring(const char short_str[], const char long_str[]) {
  // returns true iff short_str is a substring of long_str,
  // wrapping around the end of long_str
  int short_len = strlen(short_str);
  int long_len = strlen(long_str);
  if (short_len > long_len + 1) {
    return false;
  }

  // Repeat long_str to catch the case where short_str is wrapping
  char repeating[2 * long_len + 2];
  strcpy(repeating, long_str);
  repeating[long_len] = ' ';
  strcpy(repeating + long_len + 1, long_str);
  return strstr(repeating, short_str) != NULL;
}

void clear_options(WINDOW *contentwin) {
  // Wipes out options on screen
  for (int i = 0; i < 17; i++) {
    mvwprintw(contentwin, 5 + i, 1, "             ");
  }
}

// main function loop
void morse(WINDOW *contentwin, WINDOW *miscwin) {

  // cleanup
  wclear(contentwin);
  box(contentwin, 0, 0);

  // static text
  mvwprintw(contentwin, 0, getmaxx(contentwin) / 2 - 3, "MORSE");
  curs_set(1);

  mvwprintw(contentwin, 2, 1, "Morse: _____________________________");
  mvwprintw(contentwin, 4, 1, "Possible Solutions:");

  // input loop
  char morse_input[MAXLEN_MORSE];
  memset(morse_input, '\0', MAXLEN_MORSE);

  for (int i = 0; i < MAXLEN_MORSE; i++) {

    // print options
    int found = 0;
    clear_options(contentwin);

    for (int j = 0; j < 16; j++) {
      if (is_substring(morse_input, codes[j])) {
        found++;
        mvwprintw(contentwin, 5 + found, 2, "%s MHz", frequencies[j]);
      }
    }

    wmove(contentwin, 2, 8 + i);
    int c = wgetch(contentwin);

    if (c == 'q') {
      return;
    }

    if (c == 8 || c == 127) {
      if (i > 0) {
        i--;
      }
      wmove(contentwin, 2, 8 + i);
      waddch(contentwin, '_');
      morse_input[i] = '\0';
      i--;
      continue;
    }

    if (c != '.' && c != '-' && c != ' ') {
      i--;
      continue;
    }
    waddch(contentwin, c);
    morse_input[i] = c;
  }
}
