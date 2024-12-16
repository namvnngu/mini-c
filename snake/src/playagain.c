#include <math.h>
#include <ncurses.h>
#include <stdlib.h>
#include <string.h>

#include "input.h"
#include "playagain.h"

static const char *TITLE = "Your score is %d";
static const char *DESCRIPTION[2] = {
    "Press Enter to play again",
    "Press Q to quit",
};

struct playagain *playagain_new(void) {
  struct playagain *pa = malloc(sizeof(struct playagain));

  pa->width = 60;
  pa->height = 12;
  pa->startx = (COLS - pa->width) / 2;
  pa->starty = (LINES - pa->height) / 2;
  pa->win = newwin(pa->height, pa->width, pa->starty, pa->startx);

  return pa;
}

void playagain_draw(struct playagain *pa, int score) {
  int score_strlen = (int)log10(score) + 1;
  mvwprintw(pa->win, 4, (pa->width - strlen(TITLE) - score_strlen) / 2, TITLE,
            score);
  mvwprintw(pa->win, 6, (pa->width - strlen(DESCRIPTION[0])) / 2,
            DESCRIPTION[0]);
  mvwprintw(pa->win, 7, (pa->width - strlen(DESCRIPTION[1])) / 2,
            DESCRIPTION[1]);
  box(pa->win, 0, 0);
  wrefresh(pa->win);
}

int playagain_input(void) {
  while (true) {
    int key = input_getkey_block();
    if (key == QUIT || key == CONTINUE) {
      return key;
    }
  }
}

void playagain_delete(struct playagain *pa) {
  wclear(pa->win);
  wrefresh(pa->win);
  delwin(pa->win);
  free(pa);
}
