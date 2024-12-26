#ifndef _WELCOME
#define _WELCOME

#include <ncurses.h>

struct welcome {
  WINDOW *win;
  int width;
  int height;
  int startx;
  int starty;
};

int welcome_run(void);

#endif /* _WELCOME */
