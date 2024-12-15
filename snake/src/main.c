#include <ncurses.h>
#include <stdbool.h>
#include <stdlib.h>
#include <time.h>

#include "action.h"
#include "gamewin.h"
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

  enum action next_action = startwin_run();
  while (next_action != QUIT) {
    int score = gamewin_run();
    next_action = playagainwin_run(score);
  }

  endwin();
  return 0;
}
