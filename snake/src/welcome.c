#include <ncurses.h>
#include <string.h>

#include "welcome.h"
#include "win.h"

static const int WIN_WIDTH = 60;
static const int WIN_HEIGHT = 12;
static const char *TITLE = "SNAKE";
static const char *DESCRIPTION[2] = {
    "Press Enter to play",
    "Press Q to quit",
};

static WINDOW *welcome_newwin(void) {
  WINDOW *win = win_new(WIN_WIDTH, WIN_HEIGHT, (COLS - WIN_WIDTH) / 2,
                        (LINES - WIN_HEIGHT) / 2);
  win_draw(win, (WIN_WIDTH - strlen(TITLE)) / 2, 4, TITLE);
  win_draw(win, (WIN_WIDTH - strlen(DESCRIPTION[0])) / 2, 6, DESCRIPTION[0]);
  win_draw(win, (WIN_WIDTH - strlen(DESCRIPTION[1])) / 2, 7, DESCRIPTION[1]);
  return win;
}

enum win_action welcome_runwin(void) {
  WINDOW *startwin = welcome_newwin();
  while (true) {
    int key = win_getkey_block(startwin);
    if (key == 'q') {
      win_del(startwin);
      return QUIT;
    }
    if (key == '\n') {
      win_del(startwin);
      return CONTINUE;
    }
  }
}
