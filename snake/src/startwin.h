#include <ncurses.h>

#ifndef _START_WIN
#define _START_WIN

WINDOW *startwin_new(void);
void startwin_del(WINDOW *win);

#endif /* _START_WIN */
