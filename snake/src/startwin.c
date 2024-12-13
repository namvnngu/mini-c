#include <ncurses.h>
#include <string.h>

#include "startwin.h"
#include "win.h"

const int WIN_WIDTH = 60;
const int WIN_HEIGHT = 12;
const char *TITLE = "SNAKE";
const char *DESCRIPTION[2] = {
    "Press Enter to play",
    "Press Q to quit",
};

WINDOW *startwin_new(void) {
  WINDOW *win = win_new(WIN_WIDTH, WIN_HEIGHT, (COLS - WIN_WIDTH) / 2,
                        (LINES - WIN_HEIGHT) / 2);
  win_draw(win, (WIN_WIDTH - strlen(TITLE)) / 2, 4, TITLE);
  win_draw(win, (WIN_WIDTH - strlen(DESCRIPTION[0])) / 2, 6, DESCRIPTION[0]);
  win_draw(win, (WIN_WIDTH - strlen(DESCRIPTION[1])) / 2, 7, DESCRIPTION[1]);
  return win;
}
