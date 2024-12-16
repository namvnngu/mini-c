#include <ncurses.h>
#include <stdlib.h>

static void _exit(void) {
  fprintf(stderr, "Failed operation occurs");
  exit(1);
}

WINDOW *win_new(int width, int height, int startx, int starty) {
  WINDOW *win = newwin(height, width, starty, startx);
  if (win == NULL) {
    _exit();
  }

  int result;

  result = box(win, 0, 0);
  if (result == ERR) {
    _exit();
  }

  result = wrefresh(win);
  if (result == ERR) {
    _exit();
  }
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
  int result;

  result = wmove(win, starty, startx);
  if (result == ERR) {
    _exit();
  }

  va_list args;
  va_start(args, fmt);
  result = vw_printw(win, fmt, args);
  if (result == ERR) {
    _exit();
  }
  va_end(args);

}

void win_clear(WINDOW *win) {
  int result = wclear(win);
  if (result == ERR) {
    _exit();
  }
}

void win_refresh(WINDOW *win) {
  int result = wrefresh(win);
  if (result == ERR) {
    _exit();
  }
}

void win_delete(WINDOW *win) {
  int result;

  result = wclear(win);
  if (result == ERR) {
    _exit();
  }

  result = wrefresh(win);
  if (result == ERR) {
    _exit();
  }

  result = delwin(win);
  if (result == ERR) {
    _exit();
  }
}

void win_enable_color(WINDOW *win, int color) {
  int result = wattron(win, COLOR_PAIR(color));
  if (result == ERR) {
    _exit();
  }
}
void win_disable_color(WINDOW *win, int color) {
  int result = wattroff(win, COLOR_PAIR(color));
  if (result == ERR) {
    _exit();
  }
}
