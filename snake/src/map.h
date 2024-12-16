#ifndef _MAP
#define _MAP

#include <ncurses.h>

struct map {
  WINDOW *win;
  int height;
  int width;
  int startx;
  int starty;
  int border_size;
};

struct map *map_new(void);
void map_draw_point(struct map *m, int x, int y, int color);
void map_delete(struct map *m);

#endif /* _MAP */
