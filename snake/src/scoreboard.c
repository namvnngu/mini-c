#include <math.h>
#include <stdlib.h>
#include <string.h>

#include "map.h"
#include "snake.h"
#include "scoreboard.h"

static const char *TITLE = "Score";

struct scoreboard *scoreboard_new(struct map *m, struct snake *s) {
  struct scoreboard *sb = malloc(sizeof(struct scoreboard));

  sb->width = 12;
  sb->height = 5;
  sb->startx = m->startx - sb->width - 2; // 2 is gap between scoreboard and map
  sb->starty = m->starty;
  sb->win = newwin(sb->height, sb->width, sb->starty, sb->startx);
  scoreboard_set_score(sb, s);

  return sb;
}

void scoreboard_set_score(struct scoreboard *sb, struct snake *s) {
  sb->score = s->length;
}

void scoreboard_draw(struct scoreboard *sb) {
  mvwprintw(sb->win, 0, (sb->width - strlen(TITLE)) / 2, TITLE);
  int score_strlen = (int)log10(sb->score) + 1;
  mvwprintw(sb->win, (sb->height - 1) / 2, (sb->width - score_strlen) / 2, "%d",
            sb->score);
  box(sb->win, 0, 0);
  wrefresh(sb->win);
}

void scoreboard_delete(struct scoreboard *sb) {
  wclear(sb->win);
  wrefresh(sb->win);
  delwin(sb->win);
  free(sb);
}
