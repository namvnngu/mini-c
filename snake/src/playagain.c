#include <math.h>
#include <ncurses.h>
#include <string.h>

#include "input.h"
#include "playagain.h"

static const int WIN_WIDTH = 60;
static const int WIN_HEIGHT = 12;
static const char *TITLE = "YOUR SCORE IS %d";
static const char *DESCRIPTION[2] = {
    "Press Enter to play again",
    "Press Q to quit",
};

WINDOW *playagain_new(void) {
  return newwin(WIN_HEIGHT, WIN_WIDTH, (LINES - WIN_HEIGHT) / 2,
                (COLS - WIN_WIDTH) / 2);
}

void playagain_draw(WINDOW *win, int score) {
  int score_strlen = (int)log10(score) + 1;
  mvwprintw(win, 4, (WIN_WIDTH - strlen(TITLE) - score_strlen) / 2, TITLE,
            score);
  mvwprintw(win, 6, (WIN_WIDTH - strlen(DESCRIPTION[0])) / 2, DESCRIPTION[0]);
  mvwprintw(win, 7, (WIN_WIDTH - strlen(DESCRIPTION[1])) / 2, DESCRIPTION[1]);
  box(win, 0, 0);
  wrefresh(win);
}

int playagain_input(void) {
  while (true) {
    int key = input_getkey_block();
    if (key == QUIT || key == CONTINUE) {
      return key;
    }
  }
}

void playagain_delete(WINDOW *win) {
  wclear(win);
  wrefresh(win);
  delwin(win);
}
