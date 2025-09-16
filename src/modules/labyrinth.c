#include "labyrinth.h"
#include "../data/labyrinth_layouts.h"

int concat_point(int x1, int y1, int x2, int y2){
  return 1000*x1 + 100*y1 + 10*x2 + y2;
}

int min(int a, int b){
  return a < b ? a : b;
}


struct Labyrinth resolve_labyrinth(int x1, int y1, int x2, int y2){
  /* Resolve reference coordinates to labyrinth.
   * - Concatenate coordinates in lesser order
   * - then mod 24 (lowest unique) to resolve to index in lookup table. */
  int idx = min(concat_point(x1, y1, x2, y2), concat_point(x2, y2, x1, y1)) % 24;
  return get_labyrinth_layout(idx);
}

void redraw_labyrinth_specification(WINDOW* contentwin, char points[9]){
  mvwprintw(contentwin, 4, 1, "Reference: %c %c | %c %c", points[0], points[1], points[2], points[3]);
  mvwprintw(contentwin, 5, 1, "Position: %c %c", points[4], points[5]);
  mvwprintw(contentwin, 6, 1, "Target:    %c %c", points[6], points[7]);
}

int labpos_from_char(char c){
  return 2 * (c - '0') - 1;
}

void draw_labyrinth(WINDOW* contentwin, char points[9], bool draw_overlay){
  int LAB_Y = 4;
  int LAB_X = 30;
  struct Labyrinth lab = resolve_labyrinth(points[0], points[1], points[2], points[3]);

  for (int i=0; i<13; i++){
    mvwprintw(contentwin, LAB_Y+i, LAB_X, "%s", lab.layout[i]);
    // valid position overlay
    for (int j=0; j<6; j++){
      if (draw_overlay && i % 2 == 1){
        mvwprintw(contentwin, LAB_Y+i, LAB_X + 2*j + 1, "*");
      }
    }
  }

  // Start
  mvwprintw(contentwin, LAB_Y+labpos_from_char(points[5]), LAB_X+labpos_from_char(points[4]), "O");
  // Target
  mvwprintw(contentwin, LAB_Y+labpos_from_char(points[7]), LAB_X+labpos_from_char(points[6]), "X");
}


void labyrinth(WINDOW* contentwin, WINDOW* miscwin){
  // cleanup 
  wclear(contentwin);
  box(contentwin,0,0);

  // title and guide
  mvwprintw(contentwin, 0, getmaxx(contentwin)/2 - 5, "LABYRINTH");
  mvwprintw(contentwin, 1, 1, "Select labyrinth from reference points, then specify start (light / O) and end (triangle / X).");
  mvwprintw(contentwin, 2, 1, "All positions denoted by (x,y) with bottom left corner as (1,1).");


  char points[9];
  memset(points, '_', 9);
  redraw_labyrinth_specification(contentwin, points);

  // TODO add blinking (requires restructure)
  // gather input
  int c;
  for (int i=0; i<8; i++){
    c = wgetch(contentwin);
    switch(c){
      case 127: // BACKSPACE
        i-=2;
        points[i+1] = '_';
        break;
      case 'q': 
      case 27: // ESCAPE
        return;
      default:
        if (c > '0' + 6){
          i--;
          break;
        }
        points[i] = c;
        break;
    };
    redraw_labyrinth_specification(contentwin, points);
  };

  // TODO make overlay toggleable from UI
  draw_labyrinth(contentwin, points, true);


  wrefresh(contentwin);
}

