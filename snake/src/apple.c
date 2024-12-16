#include <stdlib.h>

#include "map.h"
#include "snake.h"
#include "apple.h"

static int _random_range(int min, int max) {
  return min + rand() % (max - min + 1);
}

struct apple *apple_new(struct map *m, struct snake *s) {
  struct apple *a = malloc(sizeof(struct apple));
  if (a == NULL) {
    fprintf(stderr, "Out of memory.");
    exit(1);
  }

  a->width = 1;
  a->height = 1;
  a->color = 2;
  apple_set_new_position(a, m, s);

  return a;
}

void apple_set_new_position(struct apple *a, struct map *m, struct snake *s) {
  bool found = false;
  while (!found) {
    a->x = _random_range(1, m->width - m->border_size - a->width);
    a->y = _random_range(1, m->height - m->border_size - a->height);

    bool is_within_snake_body = false;
    for (int i = 0; i < s->length; i++) {
      if (s->body[i]->x == a->x && s->body[i]->y == a->y) {
        is_within_snake_body = true;
      }
    }
    if (is_within_snake_body) {
      continue;
    }

    found = true;
  }
}

void apple_draw(struct apple *a, struct map *m) {
  map_draw_point(m, a->x, a->y, a->color);
}

void apple_delete(struct apple *a) {
  free(a);
}
