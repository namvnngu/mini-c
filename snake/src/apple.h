#ifndef _APPLE
#define _APPLE

#include "map.h"
#include "snake.h"

struct apple {
  int width;
  int height;
  int x;
  int y;
  int color;
};

struct apple *apple_new(struct map *m, struct snake *s);
void apple_draw(struct apple *ap, struct map *m);
void apple_set_new_position(struct apple *ap, struct map *m, struct snake *s);
void apple_delete(struct apple *ap);

#endif /* _APPLE */
