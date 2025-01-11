#include <ncurses.h>
#include <stdlib.h>
#include <string.h>

#include "input.h"
#include "welcome.h"

static const char *s_TITLE = "SNAKE";
static const char *s_DESCRIPTION[2] = {
  "Press enter to play",
  "Press q to quit",
};

static struct welcome *s_new(void) {
  struct welcome *wc = malloc(sizeof(struct welcome));

  wc->width = 60;
  wc->height = 12;
  wc->startx = (COLS - wc->width) / 2;
  wc->starty = (LINES - wc->height) / 2;
  wc->win = newwin(wc->height, wc->width, wc->starty, wc->startx);

  return wc;
}

static void s_draw(struct welcome *wc) {
  box(wc->win, 0, 0);

  mvwprintw(wc->win, 4, (wc->width - strlen(s_TITLE)) / 2, s_TITLE);

  int desc_len = (sizeof(s_DESCRIPTION) / sizeof(s_DESCRIPTION[0]));
  for (int i = 0; i < desc_len; i++) {
    mvwprintw(wc->win,
              6 + i,
              (wc->width - strlen(s_DESCRIPTION[i])) / 2,
              s_DESCRIPTION[i]);
  }

  wrefresh(wc->win);
}

static int s_input(void) {
  while (true) {
    int key = input_getkey_block();
    if (key == QUIT || key == CONTINUE) {
      return key;
    }
  }
}

static void s_delete(struct welcome *wc) {
  wclear(wc->win);
  wrefresh(wc->win);
  delwin(wc->win);
  free(wc);
}

int welcome_run(void) {
  struct welcome *wc = s_new();
  s_draw(wc);
  int key = s_input();
  s_delete(wc);
  return key;
}
