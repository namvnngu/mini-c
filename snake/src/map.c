#include <stdlib.h>

#include "win.h"
#include "map.h"

#define TERMINAL_WIDTH_UNIT 2

struct map *map_new(void) {
  struct map *m = malloc(sizeof(struct map));
  if (m == NULL) {
    fprintf(stderr, "Out of memory.");
    exit(1);
  }

  m->width = 25;
  m->height = 20;
  m->startx = (COLS - m->width * TERMINAL_WIDTH_UNIT) / 2;
  m->starty = (LINES - m->height) / 2;
  m->win =
      win_new(m->width * TERMINAL_WIDTH_UNIT, m->height, m->startx, m->starty);
  m->border_size = BORDER_WIDTH;

  return m;
}

void map_draw_point(struct map *m, int x, int y, int color) {
  win_enable_color(m->win, color);
  win_draw(m->win, x * TERMINAL_WIDTH_UNIT, y, "  ");
  win_disable_color(m->win, color);
}

void map_delete(struct map *m) {
  win_delete(m->win);
  free(m);
}
