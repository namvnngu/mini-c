#include <ncurses.h>
#include <string.h>

#include "input.h"
#include "welcome.h"

static const int WIN_WIDTH = 60;
static const int WIN_HEIGHT = 12;
static const char *TITLE = "SNAKE";
static const char *DESCRIPTION[2] = {
    "Press Enter to play",
    "Press Q to quit",
};

WINDOW *welcome_new(void) {
  return newwin(WIN_HEIGHT, WIN_WIDTH, (LINES - WIN_HEIGHT) / 2,
                (COLS - WIN_WIDTH) / 2);
}

void welcome_draw(WINDOW *win) {
  mvwprintw(win, 4, (WIN_WIDTH - strlen(TITLE)) / 2, TITLE);
  mvwprintw(win, 6, (WIN_WIDTH - strlen(DESCRIPTION[0])) / 2, DESCRIPTION[0]);
  mvwprintw(win, 7, (WIN_WIDTH - strlen(DESCRIPTION[1])) / 2, DESCRIPTION[1]);
  box(win, 0, 0);
  wrefresh(win);
}

int welcome_input(void) {
  while (true) {
    int key = input_getkey_block();
    if (key == QUIT || key == CONTINUE) {
      return key;
    }
  }
}

void welcome_delete(WINDOW *win) {
  wclear(win);
  wrefresh(win);
  delwin(win);
}
