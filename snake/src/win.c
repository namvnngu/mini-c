#include <ncurses.h>

#include "win.h"

WINDOW *win_new(int width, int height, int startx, int starty) {
  WINDOW *win = newwin(height, width, starty, startx);
  box(win, 0, 0);
  wrefresh(win);
  return win;
}

int win_getkey_block(WINDOW *win) {
  nodelay(win, false);
  return wgetch(win);
}
int win_getkey_nonblock(WINDOW *win) {
  nodelay(win, true);
  return wgetch(win);
}

void win_draw(WINDOW *win, int startx, int starty, const char *fmt, ...) {
  wmove(win, starty, startx);

  va_list args;
  va_start(args, fmt);
  vw_printw(win, fmt, args);
  va_end(args);

  wrefresh(win);
}

void win_clear(WINDOW *win) {
  wclear(win);
}

void win_del(WINDOW *win) {
  wclear(win);
  wrefresh(win);
  delwin(win);
}
