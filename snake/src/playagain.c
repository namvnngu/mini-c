#include <math.h>
#include <ncurses.h>
#include <string.h>

#include "playagain.h"
#include "win.h"

static const int WIN_WIDTH = 60;
static const int WIN_HEIGHT = 12;
static const char *TITLE = "YOUR SCORE IS %d";
static const char *DESCRIPTION[2] = {
    "Press Enter to play again",
    "Press Q to quit",
};

static WINDOW *_newwin(int score) {
  WINDOW *win = win_new(WIN_WIDTH, WIN_HEIGHT, (COLS - WIN_WIDTH) / 2,
                        (LINES - WIN_HEIGHT) / 2);
  int score_strlen = (int)log10(score) + 1;
  win_draw(win, (WIN_WIDTH - strlen(TITLE) - score_strlen) / 2, 4, TITLE,
           score);
  win_draw(win, (WIN_WIDTH - strlen(DESCRIPTION[0])) / 2, 6, DESCRIPTION[0]);
  win_draw(win, (WIN_WIDTH - strlen(DESCRIPTION[1])) / 2, 7, DESCRIPTION[1]);
  return win;
}

enum win_action playagain_runwin(int score) {
  WINDOW *win = _newwin(100);
  while (true) {
    int key = win_getkey_block(win);
    if (key == 'q') {
      win_delete(win);
      return QUIT;
    }
    if (key == '\n') {
      win_delete(win);
      return CONTINUE;
    }
  }
}