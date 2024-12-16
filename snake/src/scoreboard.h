#ifndef _SCOREBOARD
#define _SCOREBOARD

#include <ncurses.h>

struct scoreboard {
  WINDOW *win;
  int score;
};

struct scoreboard *scoreboard_new(struct map *m, int snake_length);
void scoreboard_update_score(struct scoreboard *s, int snake_length);
void scoreboard_delete(struct scoreboard *s);

#endif /* _SCOREBOARD */
