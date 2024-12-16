#ifndef _APPLE
#define _APPLE

struct apple {
  int width;
  int height;
  int x;
  int y;
  int color;
};

struct apple *apple_new(struct map *m, struct snake *s);
void apple_set_new_position(struct apple *a, struct map *m, struct snake *s);
void apple_draw(struct apple *a, struct map *m);
void apple_delete(struct apple *a);

#endif /* _APPLE */
