#include <locale.h>
#include <wchar.h>
#include "glyphs.h"


void glyphs(WINDOW* contentwin, WINDOW* miscwin){
  // reminder for batteries and label
  char *msgs[] = {"Complex wires rely on", "- Indicators", "- Battery count"};
  log_to_misc_many(miscwin, msgs, 3);
  // title and guide
  mvwprintw(contentwin, 0, getmaxx(contentwin)/2 - 6, "GLYPHS");
  mvwprintw(contentwin, 1, 1, "Input Glyphs, then click in displayed order.");



  wrefresh(contentwin);

}

