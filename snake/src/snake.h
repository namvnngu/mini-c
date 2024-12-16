#ifndef _SNAKE
#define _SNAKE

struct snake_body {
  int width;
  int height;
  int x;
  int y;
};

enum snake_direction {
  NORTH,
  EAST,
  SOUTH,
  WEST,
};

struct snake {
  struct snake_body **body;
  enum snake_direction direction;
  int length;
  int color;
};

struct snake *snake_new(struct map *m);
void snake_update(struct snake *s, int key_input);
bool snake_hit_itself(struct snake *s);
bool snake_hit_apple(struct snake *s, int applex, int appley);
bool snake_hit_map_wall(struct snake *s, struct map *m);
void snake_draw(struct snake *s, struct map *m);
void snake_delete(struct snake *s);

#endif /* _SNAKE */
