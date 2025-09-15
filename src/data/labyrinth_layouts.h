#ifndef LABLAYOUTS_H
#define LABLAYOUTS_H

#include <string.h>

struct Labyrinth {
  char layout[14][14];
};

struct Labyrinth get_labyrinth_layout(int idx);

#endif
