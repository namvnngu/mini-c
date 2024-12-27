#include <ncurses.h>
#include <stdlib.h>
#include <string.h>

#include "input.h"
#include "welcome.h"

static const char *TITLE = "SNAKE";
static const char *DESCRIPTION[2] = {
    "Press enter to play",
    "Press q to quit",
};

static struct welcome *_new(void) {
  struct welcome *wc = malloc(sizeof(struct welcome));

  wc->width = 60;
  wc->height = 12;
  wc->startx = (COLS - wc->width) / 2;
  wc->starty = (LINES - wc->height) / 2;
  wc->win = newwin(wc->height, wc->width, wc->starty, wc->startx);

  return wc;
}

static void _draw(struct welcome *wc) {
  box(wc->win, 0, 0);

  mvwprintw(wc->win, 4, (wc->width - strlen(TITLE)) / 2, TITLE);

  int desc_len = (sizeof(DESCRIPTION) / sizeof(DESCRIPTION[0]));
  for (int i = 0; i < desc_len; i++) {
    mvwprintw(wc->win, 6 + i, (wc->width - strlen(DESCRIPTION[i])) / 2,
              DESCRIPTION[i]);
  }

  wrefresh(wc->win);
}

static int _input(void) {
  while (true) {
    int key = input_getkey_block();
    if (key == QUIT || key == CONTINUE) {
      return key;
    }
  }
}

static void _delete(struct welcome *wc) {
  wclear(wc->win);
  wrefresh(wc->win);
  delwin(wc->win);
  free(wc);
}

int welcome_run(void) {
  struct welcome *wc = _new();
  _draw(wc);
  int key = _input();
  _delete(wc);
  return key;
}
