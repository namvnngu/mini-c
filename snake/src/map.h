#ifndef _MAP
#define _MAP

#include <ncurses.h>

struct map {
  WINDOW *win;
  int height;
  int width;
  int startx;
  int starty;
};

struct map *map_new(void);
void map_drawer_point(struct map *m, int x, int y, int color);
void map_delete(struct map *m);

#endif /* _MAP */