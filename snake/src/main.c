#include <ncurses.h>
#include <stdbool.h>
#include <stdlib.h>
#include <time.h>

#include "flowcmd.h"
#include "game.h"
#include "playagainwin.h"
#include "startwin.h"

int main(int argc, char **argv) {
  srand(time(NULL));

  initscr();            // Initialize the screen
  cbreak();             // Disable line buffering
  noecho();             // Do not show typed characters
  curs_set(false);      // Hide the cursor
  keypad(stdscr, true); // Enable special keys like arrows
  start_color();        // Enable colors (create colors and color pairs)
  use_default_colors(); // Allow default terminal colors
  refresh();            // Draw the screen

  enum flowcmd cmd = startwin_run();
  while (cmd != QUIT) {
    game_run();
    cmd = playagainwin_run(100);
  }

  endwin();
  return 0;
}
