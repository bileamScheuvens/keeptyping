#include "labyrinth_layouts.h"


struct Labyrinth get_labyrinth_layout(int idx){
  struct Labyrinth labyrinth;
  switch(idx){
    // lab 1: (1,5), (6,4) % 24 = 4
    case 4:
      strcpy(labyrinth.layout[0],  "+-----+-----+");
      strcpy(labyrinth.layout[1],  "|     |     |");
      strcpy(labyrinth.layout[2],  "| +-- | ----+");
      strcpy(labyrinth.layout[3],  "| |   |     |");
      strcpy(labyrinth.layout[4],  "| | --+---- |");
      strcpy(labyrinth.layout[5],  "| |   |     |");
      strcpy(labyrinth.layout[6],  "| +-- | +-- |");
      strcpy(labyrinth.layout[7],  "| |     |   |");
      strcpy(labyrinth.layout[8],  "| +---+-+-+ |");
      strcpy(labyrinth.layout[9],  "|     |   | |");
      strcpy(labyrinth.layout[10], "| --+   +-+ |");
      strcpy(labyrinth.layout[11], "|   |   |   |");
      strcpy(labyrinth.layout[12], "+-----------+");
      break;
    // lab 2: (2,3), (5,5) % 24 = 3
    case 3:
      strcpy(labyrinth.layout[0],  "+-----+-----+");
      strcpy(labyrinth.layout[1],  "|     |     |");
      strcpy(labyrinth.layout[2],  "+-- +-+ + --+");
      strcpy(labyrinth.layout[3],  "|   |   |   |");
      strcpy(labyrinth.layout[4],  "| +-+ +-+-- |");
      strcpy(labyrinth.layout[5],  "| |   |     |");
      strcpy(labyrinth.layout[6],  "| | +-+ +-+ |");
      strcpy(labyrinth.layout[7],  "|   |   | | |");
      strcpy(labyrinth.layout[8],  "| +-+ +-+ | |");
      strcpy(labyrinth.layout[9],  "| | | |   | |");
      strcpy(labyrinth.layout[10], "| | | |  -+ |");
      strcpy(labyrinth.layout[11], "| |   |     |");
      strcpy(labyrinth.layout[12], "+-----------+");
      break;
    // lab 3: (4,3), (6,3) % 24 = 19
    case 19:
      strcpy(labyrinth.layout[0],  "+-----+-+---+");
      strcpy(labyrinth.layout[1],  "|     | |   |");
      strcpy(labyrinth.layout[2],  "| +-+ |   | |");
      strcpy(labyrinth.layout[3],  "| | | |   | |");
      strcpy(labyrinth.layout[4],  "|-+ | +---+ |");
      strcpy(labyrinth.layout[5],  "|   | |   | |");
      strcpy(labyrinth.layout[6],  "|   | | | | |");
      strcpy(labyrinth.layout[7],  "| | | | | | |");
      strcpy(labyrinth.layout[8],  "| | | | | | |");
      strcpy(labyrinth.layout[9],  "| |   | | | |");
      strcpy(labyrinth.layout[10], "| +---+ | | |");
      strcpy(labyrinth.layout[11], "|       |   |");
      strcpy(labyrinth.layout[12], "+-------+---+");
      break;
    // lab 4: (1,3), (1,6) % 24 = 20
    case 20:
      strcpy(labyrinth.layout[0],  "+---+-------+");
      strcpy(labyrinth.layout[1],  "|   |       |");
      strcpy(labyrinth.layout[2],  "| | +------ |");
      strcpy(labyrinth.layout[3],  "| | |       |");
      strcpy(labyrinth.layout[4],  "| | | +---+ |");
      strcpy(labyrinth.layout[5],  "| |   |   | |");
      strcpy(labyrinth.layout[6],  "| +---+ --+ |");
      strcpy(labyrinth.layout[7],  "| |         |");
      strcpy(labyrinth.layout[8],  "| +-------+ |");
      strcpy(labyrinth.layout[9],  "|         | |");
      strcpy(labyrinth.layout[10], "| ----+-- | |");
      strcpy(labyrinth.layout[11], "|     |   | |");
      strcpy(labyrinth.layout[12], "+---------+-+");
      break;
    // lab 5: (4,1), (5,4) % 24 = 2
    case 2:
      strcpy(labyrinth.layout[0],  "+-----------+");
      strcpy(labyrinth.layout[1],  "|           |");
      strcpy(labyrinth.layout[2],  "+-------- + |");
      strcpy(labyrinth.layout[3],  "|         | |");
      strcpy(labyrinth.layout[4],  "| --+-- +-+-+");
      strcpy(labyrinth.layout[5],  "|   |   |   |");
      strcpy(labyrinth.layout[6],  "| | +---+ | |");
      strcpy(labyrinth.layout[7],  "| |     | | |");
      strcpy(labyrinth.layout[8],  "| +---- +-+ |");
      strcpy(labyrinth.layout[9],  "| |       | |");
      strcpy(labyrinth.layout[10], "| | ------+ |");
      strcpy(labyrinth.layout[11], "| |         |");
      strcpy(labyrinth.layout[12], "+-+---------+");
      break;
    // lab 6: (3,2), (5,6) % 24 = 16
    case 16:
      strcpy(labyrinth.layout[0],  "+-+---+-----+");
      strcpy(labyrinth.layout[1],  "| |   |     |");
      strcpy(labyrinth.layout[2],  "| | | +-- + |");
      strcpy(labyrinth.layout[3],  "| | | |   | |");
      strcpy(labyrinth.layout[4],  "|   | | +-+ |");
      strcpy(labyrinth.layout[5],  "|   | | |   |");
      strcpy(labyrinth.layout[6],  "| --+-+ | +-+");
      strcpy(labyrinth.layout[7],  "|   |   | | |");
      strcpy(labyrinth.layout[8],  "+-- | | | | |");
      strcpy(labyrinth.layout[9],  "|   | | |   |");
      strcpy(labyrinth.layout[10], "| --+-+ +-- |");
      strcpy(labyrinth.layout[11], "|       |   |");
      strcpy(labyrinth.layout[12], "+-------+---+");
      break;
    // lab 7: (2,1), (2,6) % 24 = 14
    case 14:
      strcpy(labyrinth.layout[0],  "+-------+---+");
      strcpy(labyrinth.layout[1],  "|       |   |");
      strcpy(labyrinth.layout[2],  "| +---+   | |");
      strcpy(labyrinth.layout[3],  "| |   |   | |");
      strcpy(labyrinth.layout[4],  "| | +-+-+-+ |");
      strcpy(labyrinth.layout[5],  "|   |   |   |");
      strcpy(labyrinth.layout[6],  "+---+ --+ +-|");
      strcpy(labyrinth.layout[7],  "|   |     | |");
      strcpy(labyrinth.layout[8],  "| | | ----+ |");
      strcpy(labyrinth.layout[9],  "| | |     | |");
      strcpy(labyrinth.layout[10], "| +-+---- | |");
      strcpy(labyrinth.layout[11], "|           |");
      strcpy(labyrinth.layout[12], "+-----------+");
      break;
    // lab 8: (3,3), (4,6) % 24 = 10
    case 10:
      strcpy(labyrinth.layout[0],  "+-+-----+---+");
      strcpy(labyrinth.layout[1],  "| |     |   |");
      strcpy(labyrinth.layout[2],  "|   --+ | | |");
      strcpy(labyrinth.layout[3],  "|     |   | |");
      strcpy(labyrinth.layout[4],  "| +---+---+ |");
      strcpy(labyrinth.layout[5],  "| |       | |");
      strcpy(labyrinth.layout[6],  "| | --+-- | |");
      strcpy(labyrinth.layout[7],  "| |   |     |");
      strcpy(labyrinth.layout[8],  "| +-+ +-----+");
      strcpy(labyrinth.layout[9],  "| | |       |");
      strcpy(labyrinth.layout[10], "| | +-------+");
      strcpy(labyrinth.layout[11], "|           |");
      strcpy(labyrinth.layout[12], "+-----------+");
      break;
    // lab 9: (1,2), (3,5) % 24 = 11
    case 11:
      strcpy(labyrinth.layout[0],  "+-+---------+");
      strcpy(labyrinth.layout[1],  "| |         |");
      strcpy(labyrinth.layout[2],  "| | +---+ | |");
      strcpy(labyrinth.layout[3],  "| | |   | | |");
      strcpy(labyrinth.layout[4],  "|     +-+ | |");
      strcpy(labyrinth.layout[5],  "|     |   | |");
      strcpy(labyrinth.layout[6],  "| +-+-+ +-+ |");
      strcpy(labyrinth.layout[7],  "| | |   |   |");
      strcpy(labyrinth.layout[8],  "| | | +-+-+ |");
      strcpy(labyrinth.layout[9],  "| | | |   | |");
      strcpy(labyrinth.layout[10], "| | | | | +-+");
      strcpy(labyrinth.layout[11], "|   |   |   |");
      strcpy(labyrinth.layout[12], "+---+---+---+");
      break;
  }
  return labyrinth;
}


