#include "config.h"


void init_color_pairs(){
  init_pair(PAIR_REGULAR, COLOR_WHITE, COLOR_BLACK);
  // use yellow for gray
  init_color(COLOR_YELLOW, 300, 300, 300);
  init_pair(PAIR_DISABLED, COLOR_YELLOW, COLOR_BLACK);
  init_pair(PAIR_REDONBLACK, COLOR_RED, COLOR_BLACK); 
  init_pair(PAIR_BLUEONBLACK, COLOR_BLUE, COLOR_BLACK);
  init_pair(PAIR_GREENONBLACK, COLOR_GREEN, COLOR_BLACK); 
}

void disable_text(WINDOW* window, bool disable){
  if (disable) {
    wattron(window, COLOR_PAIR(PAIR_DISABLED));
  } else {
    wattron(window, COLOR_PAIR(PAIR_REGULAR));
  }
}

Settings settings;

void set_locale(char locale[3]){
  strcpy(settings.locale, locale);
}

void set_alt_sequence_wires(bool use_alt){
  settings.alt_sequence_wires = use_alt;
}

void write_settings(){
  /* Serialize settings and write to file. */
  FILE *file = fopen(SETTING_FILENAME, "wb");
  if (file == NULL) {
      // TODO maybe print error to miscwin
      // perror("Failed to open file");
      return;
  }
  fwrite(&settings, sizeof(settings), 1, file);
  fclose(file);
}

void read_settings() {
  /* Deserialize settings from file. If no file exists, initalize settings with defaults. */
  FILE *file = fopen(SETTING_FILENAME, "rb");
  if (file == NULL) {
    // default settings
    set_locale("en");
    set_alt_sequence_wires( false);
    return;
  }
  size_t _ = fread(&settings, sizeof(settings), 1, file);
  fclose(file);
}
