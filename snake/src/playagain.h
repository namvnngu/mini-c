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

struct playagain *playagain_new(void);
void playagain_draw(struct playagain *pa, int score);
int playagain_input(void);
void playagain_delete(struct playagain *pa);

#endif /* _PLAYAGAIN */
