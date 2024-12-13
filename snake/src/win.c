#include <ncurses.h>

#include "win.h"

WINDOW *win_new(int width, int height, int startx, int starty) {
  WINDOW *win = newwin(height, width, starty, startx);
  box(win, 0, 0);
  wrefresh(win);
  return win;
}

int win_get_key_block(WINDOW *win) {
  nodelay(win, false);
  return wgetch(win);
}
int win_get_key_nonblock(WINDOW *win) {
  nodelay(win, true);
  return wgetch(win);
}

void win_draw(WINDOW *win, int startx, int starty, const char *fmt, ...) {
  va_list ap;
  va_start(ap, fmt);
  mvwprintw(win, starty, startx, fmt, ap);
  va_end(ap);
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
