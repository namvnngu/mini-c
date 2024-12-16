#include <ncurses.h>
#include <stdlib.h>
#include <string.h>

#include "input.h"
#include "welcome.h"

static const char *TITLE = "SNAKE";
static const char *DESCRIPTION[2] = {
    "Press Enter to play",
    "Press Q to quit",
};

struct welcome *welcome_new(void) {
  struct welcome *wc = malloc(sizeof(struct welcome));

  wc->width = 60;
  wc->height = 12;
  wc->startx = (COLS - wc->width) / 2;
  wc->starty = (LINES - wc->height) / 2;
  wc->win = newwin(wc->height, wc->width, wc->starty, wc->startx);

  return wc;
}

void welcome_draw(struct welcome *wc) {
  mvwprintw(wc->win, 4, (wc->width - strlen(TITLE)) / 2, TITLE);
  mvwprintw(wc->win, 6, (wc->width - strlen(DESCRIPTION[0])) / 2,
            DESCRIPTION[0]);
  mvwprintw(wc->win, 7, (wc->width - strlen(DESCRIPTION[1])) / 2,
            DESCRIPTION[1]);
  box(wc->win, 0, 0);
  wrefresh(wc->win);
}

int welcome_input(void) {
  while (true) {
    int key = input_getkey_block();
    if (key == QUIT || key == CONTINUE) {
      return key;
    }
  }
}

void welcome_delete(struct welcome *wc) {
  wclear(wc->win);
  wrefresh(wc->win);
  delwin(wc->win);
  free(wc);
}
