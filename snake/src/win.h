#ifndef _WINDOW
#define _WINDOW

#include <ncurses.h>

WINDOW *win_new(int width, int height, int startx, int starty);
int win_getkey_block(WINDOW *win);
int win_getkey_nonblock(WINDOW *win);
void win_draw(WINDOW *win, int startx, int starty, const char *fmt, ...);
void win_clear(WINDOW *win);
void win_del(WINDOW *win);

#endif /* _WINDOW */
