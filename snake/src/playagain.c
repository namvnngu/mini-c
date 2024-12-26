#include <math.h>
#include <ncurses.h>
#include <stdlib.h>
#include <string.h>

#include "input.h"
#include "playagain.h"

static const char *TITLE = "Your score is %d";
static const char *DESCRIPTION[2] = {
    "Press enter to play again",
    "Press q to quit",
};

static struct playagain *_playagain_new(void) {
  struct playagain *pa = malloc(sizeof(struct playagain));

  pa->width = 60;
  pa->height = 12;
  pa->startx = (COLS - pa->width) / 2;
  pa->starty = (LINES - pa->height) / 2;
  pa->win = newwin(pa->height, pa->width, pa->starty, pa->startx);

  return pa;
}

static void _playagain_draw(struct playagain *pa, int score) {
  box(pa->win, 0, 0);

  int score_strlen = (int)log10(score) + 1;
  mvwprintw(pa->win, 4, (pa->width - strlen(TITLE) - score_strlen) / 2, TITLE,
            score);

  int desc_len = (sizeof(DESCRIPTION) / sizeof(DESCRIPTION[0]));
  for (int i = 0; i < desc_len; i++) {
    mvwprintw(pa->win, 6 + i, (pa->width - strlen(DESCRIPTION[i])) / 2,
              DESCRIPTION[i]);
  }

  wrefresh(pa->win);
}

static int _playagain_input(void) {
  while (true) {
    int key = input_getkey_block();
    if (key == QUIT || key == CONTINUE) {
      return key;
    }
  }
}

static void _playagain_delete(struct playagain *pa) {
  wclear(pa->win);
  wrefresh(pa->win);
  delwin(pa->win);
  free(pa);
}

int playagain_run(int score) {
  struct playagain *pa = _playagain_new();
  _playagain_draw(pa, score);
  int key = _playagain_input();
  _playagain_delete(pa);
  return key;
}
