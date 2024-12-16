#include <stdbool.h>

#include "map.h"
#include "snake.h"

struct snake *snake_new(struct map *m) {
  struct snake *s;
  return s;
}

void snake_update(struct snake *s, int key_input) {
}

bool snake_hit_itself(struct snake *s) {
  return false;
}

bool snake_hit_apple(struct snake *s, int applex, int appley) {
  return false;
}

bool snake_hit_map_wall(struct snake *s, struct map *m) {
  return false;
}

void snake_draw(struct snake *s, struct map *m) {
}

void snake_delete(struct snake *s) {
}
