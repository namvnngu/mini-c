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

struct welcome *welcome_new(void);
void welcome_draw(struct welcome *wc);
int welcome_input(void);
void welcome_delete(struct welcome *wc);

#endif /* _WELCOME */
