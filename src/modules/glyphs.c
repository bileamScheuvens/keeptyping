#include <locale.h>
#include <wchar.h>
#include "glyphs.h"


void glyphs(WINDOW* contentwin, WINDOW* miscwin){
  // cleanup 
  wclear(contentwin);
  box(contentwin,0,0);

  // title and guide
  mvwprintw(contentwin, 0, getmaxx(contentwin)/2 - 6, "GLYPHS");
  mvwprintw(contentwin, 1, 1, "Input Glyphs, then click in displayed order.");



  wrefresh(contentwin);

}

