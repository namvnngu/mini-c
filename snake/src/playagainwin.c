#include <math.h>
#include <ncurses.h>
#include <string.h>

#include "flowcmd.h"
#include "playagainwin.h"
#include "win.h"

static const int WIN_WIDTH = 60;
static const int WIN_HEIGHT = 12;
static const char *TITLE = "YOUR SCORE IS %d";
static const char *DESCRIPTION[2] = {
    "Press Enter to play again",
    "Press Q to quit",
};

static WINDOW *playagainwin_new(int score) {
  WINDOW *win = win_new(WIN_WIDTH, WIN_HEIGHT, (COLS - WIN_WIDTH) / 2,
                        (LINES - WIN_HEIGHT) / 2);
  int score_strlen = (int)log10(score) + 1;
  win_draw(win, (WIN_WIDTH - strlen(TITLE) - score_strlen) / 2, 4, TITLE,
           score);
  win_draw(win, (WIN_WIDTH - strlen(DESCRIPTION[0])) / 2, 6, DESCRIPTION[0]);
  win_draw(win, (WIN_WIDTH - strlen(DESCRIPTION[1])) / 2, 7, DESCRIPTION[1]);
  return win;
}

enum flowcmd playagainwin_run(int score) {
  WINDOW *playagainwin = playagainwin_new(100);
  while (true) {
    int key = win_getkey_block(playagainwin);
    if (key == 'q') {
      return QUIT;
    }
    if (key == '\n') {
      win_del(playagainwin);
      return CONTINUE;
    }
  }
}
