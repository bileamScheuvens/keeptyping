#ifndef CONFIG_H
#define CONFIG_H

#include <stdio.h>
#include <stdbool.h>
#include <string.h>

#include <ncurses.h>

// integer mapping for colors 
#define RED 1
#define BLUE 2
#define BLACK 3
#define WHITE 4
#define YELLOW 5

// color pairs
#define PAIR_REGULAR 1
#define PAIR_DISABLED 2
#define PAIR_REDONBLACK 3 
#define PAIR_BLUEONBLACK 4 
#define PAIR_GREENONBLACK 5 

#define SETTING_FILENAME "settings.dat"

void init_color_pairs();
void disable_text(WINDOW* window, bool disable);

typedef struct __Settings {
  char locale[3];
  bool alt_sequence_wires;
} Settings;

extern Settings settings;

void write_settings();

void read_settings();

void set_locale(char locale[3]);

void set_alt_sequence_wires(bool use_alt);


#endif
