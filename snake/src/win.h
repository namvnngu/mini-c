#include <ncurses.h>

#ifndef _WINDOW
#define _WINDOW

enum win_cmd {
  NEXT,
  QUIT
};

WINDOW *win_new(int width, int height, int startx, int starty);
int win_get_key_block(WINDOW *win);
int win_get_key_nonblock(WINDOW *win);
void win_draw(WINDOW *win, int startx, int starty, const char *fmt, ...);
void win_clear(WINDOW *win);
void win_del(WINDOW *win);

#endif /* _WINDOW */
