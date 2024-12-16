#include <ncurses.h>
#include <stdbool.h>
#include <stdlib.h>
#include <time.h>

#include "game.h"
#include "input.h"
#include "playagain.h"
#include "welcome.h"

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

  int key;

  WINDOW *wc = welcome_new();
  welcome_draw(wc);
  key = welcome_input();
  welcome_delete(wc);

  while (key != QUIT) {
    int score = game_run();

    WINDOW *pa = playagain_new();
    playagain_draw(pa, score);
    key = playagain_input();
    playagain_delete(pa);
  }

  endwin();
  return 0;
}
