#ifndef _PLAYAGAIN_WIN
#define _PLAYAGAIN_WIN

#include <ncurses.h>

WINDOW *playagain_new(void);
void playagain_draw(WINDOW *win, int score);
int playagain_input(void);
void playagain_delete(WINDOW *win);

#endif /* _PLAYAGAIN_WIN */
