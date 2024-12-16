#include <ncurses.h>
#include <unistd.h>

#include "map.h"
#include "snake.h"
#include "apple.h"
#include "scoreboard.h"
#include "game.h"
#include "input.h"

int game_run(void) {
  struct map *m = map_new();
  struct snake *s = snake_new(m);
  struct apple *ap = apple_new(m, s);
  struct scoreboard *sb = scoreboard_new(m, s);

  int score = 0;
  bool is_over = false;

  while (!is_over) {
    int key = input_getkey_nonblock();

    snake_update_keyinput(s, key);
    if (snake_hit_map_wall(s, m) || snake_hit_itself(s)) {
      is_over = true;
      continue;
    }
    if (snake_hit_apple(s, ap->x, ap->y)) {
      snake_update_after_hit_apple(s);
      apple_set_new_position(ap, m, s);
      scoreboard_set_score(sb, s);
    }

    apple_draw(ap, m);
    snake_draw(s, m);
    map_draw(m);
    scoreboard_draw(sb);

    usleep(75000);

    map_clear(m);
    scoreboard_clear(sb);
  }

  score = sb->score;

  scoreboard_delete(sb);
  apple_delete(ap);
  snake_delete(s);
  map_delete(m);

  return score;
}
