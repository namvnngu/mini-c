#include <ncurses.h>
#include <stdlib.h>
#include <string.h>

#include "input.h"
#include "welcome.h"

static const char *PRV_TITLE = "SNAKE";
static const char *PRV_DESCRIPTION[2] = {
    "Press enter to play",
    "Press q to quit",
};

static struct welcome *prv_new(void) {
  struct welcome *wc = malloc(sizeof(struct welcome));

  wc->width = 60;
  wc->height = 12;
  wc->startx = (COLS - wc->width) / 2;
  wc->starty = (LINES - wc->height) / 2;
  wc->win = newwin(wc->height, wc->width, wc->starty, wc->startx);

  return wc;
}

static void prv_draw(struct welcome *wc) {
  box(wc->win, 0, 0);

  mvwprintw(wc->win, 4, (wc->width - strlen(PRV_TITLE)) / 2, PRV_TITLE);

  int desc_len = (sizeof(PRV_DESCRIPTION) / sizeof(PRV_DESCRIPTION[0]));
  for (int i = 0; i < desc_len; i++) {
    mvwprintw(wc->win, 6 + i, (wc->width - strlen(PRV_DESCRIPTION[i])) / 2,
              PRV_DESCRIPTION[i]);
  }

  wrefresh(wc->win);
}

static int prv_input(void) {
  while (true) {
    int key = input_getkey_block();
    if (key == QUIT || key == CONTINUE) {
      return key;
    }
  }
}

static void prv_delete(struct welcome *wc) {
  wclear(wc->win);
  wrefresh(wc->win);
  delwin(wc->win);
  free(wc);
}

int welcome_run(void) {
  struct welcome *wc = prv_new();
  prv_draw(wc);
  int key = prv_input();
  prv_delete(wc);
  return key;
}
