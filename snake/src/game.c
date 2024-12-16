#include <ncurses.h>
#include <unistd.h>

#include "map.h"
#include "win.h"
#include "snake.h"
#include "apple.h"
#include "scoreboard.h"
#include "game.h"

int game_runwin(void) {
  struct map *map = map_new();
  struct snake *snake = snake_new(map);
  struct apple *apple = apple_new();
  struct scoreboard *scoreboard = scoreboard_new(map, snake->length);
  bool is_over = false;

  while (!is_over) {
    int key = win_getkey_nonblock(map->win);

    win_clear(map->win);
    win_clear(scoreboard->win);

    snake_update(snake, key);
    if (snake_hit_map_wall(snake, map) || snake_hit_itself(snake)) {
      is_over = true;
      continue;
    }
    if (snake_hit_apple(snake, apple->x, apple->y)) {
      apple_set_new_position(apple, map, snake->body);
      scoreboard_update_score(scoreboard, snake->length);
    }

    snake_draw(snake, map);
    apple_draw(apple, map);

    win_refresh(map->win);
    win_refresh(scoreboard->win);

    usleep(75000);
  }

  scoreboard_delete(scoreboard);
  apple_delete(apple);
  snake_delete(snake);
  map_delete(map);

  return 100;
}
