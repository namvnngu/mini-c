#include <math.h>
#include <ncurses.h>
#include <stdlib.h>
#include <string.h>

#include "input.h"
#include "playagain.h"

static const char *PRV_TITLE = "Your score is %d";
static const char *PRV_DESCRIPTION[2] = {
    "Press enter to play again",
    "Press q to quit",
};

static struct playagain *prv_new(void) {
  struct playagain *pa = malloc(sizeof(struct playagain));

  pa->width = 60;
  pa->height = 12;
  pa->startx = (COLS - pa->width) / 2;
  pa->starty = (LINES - pa->height) / 2;
  pa->win = newwin(pa->height, pa->width, pa->starty, pa->startx);

  return pa;
}

static void prv_draw(struct playagain *pa, int score) {
  box(pa->win, 0, 0);

  int score_strlen = (int)log10(score) + 1;
  mvwprintw(pa->win, 4, (pa->width - strlen(PRV_TITLE) - score_strlen) / 2,
            PRV_TITLE, score);

  int desc_len = (sizeof(PRV_DESCRIPTION) / sizeof(PRV_DESCRIPTION[0]));
  for (int i = 0; i < desc_len; i++) {
    mvwprintw(pa->win, 6 + i, (pa->width - strlen(PRV_DESCRIPTION[i])) / 2,
              PRV_DESCRIPTION[i]);
  }

  wrefresh(pa->win);
}

static int prv_input(void) {
  while (true) {
    int key = input_getkey_block();
    if (key == QUIT || key == CONTINUE) {
      return key;
    }
  }
}

static void prv_delete(struct playagain *pa) {
  wclear(pa->win);
  wrefresh(pa->win);
  delwin(pa->win);
  free(pa);
}

int playagain_run(int score) {
  struct playagain *pa = prv_new();
  prv_draw(pa, score);
  int key = prv_input();
  prv_delete(pa);
  return key;
}
