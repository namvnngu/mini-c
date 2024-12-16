#ifndef _SCOREBOARD
#define _SCOREBOARD

#include <ncurses.h>

struct scoreboard {
  WINDOW *win;
  int score;
};

struct scoreboard *scoreboard_new(struct map *m, struct snake *s);
void scoreboard_update_score(struct scoreboard *sb, struct snake *s);
void scoreboard_delete(struct scoreboard *sb);

#endif /* _SCOREBOARD */
