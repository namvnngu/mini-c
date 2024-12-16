#ifndef _WINDOW
#define _WINDOW

#include <ncurses.h>

#define BORDER_WIDTH 1;

enum win_action {
  CONTINUE,
  QUIT
};

WINDOW *win_new(int width, int height, int startx, int starty);
int win_getkey_block(WINDOW *win);
int win_getkey_nonblock(WINDOW *win);
void win_draw(WINDOW *win, int startx, int starty, const char *fmt, ...);
void win_clear(WINDOW *win);
void win_refresh(WINDOW *win);
void win_delete(WINDOW *win);
void win_enable_color(WINDOW *win, int color);
void win_disable_color(WINDOW *win, int color);

#endif /* _WINDOW */
