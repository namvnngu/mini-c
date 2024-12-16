#ifndef _START_WIN
#define _START_WIN

#include <ncurses.h>

WINDOW *welcome_new(void);
void welcome_draw(WINDOW *win);
int welcome_input(void);
void welcome_delete(WINDOW *win);

#endif /* _START_WIN */
