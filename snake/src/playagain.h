#ifndef _PLAYAGAIN
#define _PLAYAGAIN

#include <ncurses.h>

struct playagain {
  WINDOW *win;
  int width;
  int height;
  int startx;
  int starty;
};

int playagain_run(int score);

#endif /* _PLAYAGAIN */
