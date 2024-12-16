#include <ncurses.h>
#include <stdbool.h>
#include <stdlib.h>
#include <time.h>

#include "game.h"
#include "playagain.h"
#include "welcome.h"
#include "win.h"

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
  init_pair(1, -1, COLOR_BLUE);
  init_pair(2, -1, COLOR_RED);

  enum win_action next_action = welcome_runwin();
  while (next_action != QUIT) {
    int score = game_runwin();
    next_action = playagain_runwin(score);
  }

  endwin();
  return 0;
}
