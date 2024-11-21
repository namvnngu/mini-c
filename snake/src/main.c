#include <ncurses.h>
#include <stdbool.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

#define DELAY_IN_MICROSECOND 100000

#define SNAKE_MAX_LENGTH 256

struct Vec2 {
  int x;
  int y;
};

struct Snake {
  struct Vec2 positions[SNAKE_MAX_LENGTH];
  struct Vec2 last_positions[SNAKE_MAX_LENGTH];
  struct Vec2 speed;
  int length;
};

void setup(void);
void update(void);
void draw(void);

int rand_int(int min, int max);

int screen_width = 0;
int screen_height = 0;

WINDOW *game_box;
int game_box_width;
int game_box_height;
const char GAME_BOX_MARGIN_INLINE = 15;
const char GAME_BOX_MARGIN_BLOCK = 5;

struct Vec2 apple;
const char *APPLE = "@";

const char *SNAKE_HEAD = "x";
const char *SNAKE_BODY = "*";
struct Snake snake;

bool over = false;

int main(int argc, char **argv) {
  setup();
  update();
  return 0;
}

void setup(void) {
  initscr();
  noecho();
  cbreak();
  curs_set(FALSE);
  keypad(stdscr, TRUE);
  nodelay(stdscr, TRUE);

  getmaxyx(stdscr, screen_height, screen_width);
  game_box_width = screen_width - GAME_BOX_MARGIN_INLINE * 2;
  game_box_height = screen_height - GAME_BOX_MARGIN_BLOCK * 2;
  game_box = newwin(game_box_height, game_box_width, GAME_BOX_MARGIN_BLOCK,
                    GAME_BOX_MARGIN_INLINE);

  apple.x = rand_int(4, game_box_width - 2);
  apple.y = rand_int(4, game_box_height - 2);

  /*snake.length = 1;*/
  /*snake.parts[0].x = 1;*/
  /*snake.parts[0].y = 1;*/
  /*snake.speed.x = 2;*/
  /*snake.speed.y = 0;*/

  snake.length = 4;
  snake.positions[0].x = 4;
  snake.positions[0].y = 1;
  snake.positions[1].x = 3;
  snake.positions[1].y = 1;
  snake.positions[2].x = 2;
  snake.positions[2].y = 1;
  snake.positions[3].x = 1;
  snake.positions[3].y = 1;
  snake.speed.x = 2;
  snake.speed.y = 0;
}

void update(void) {
  int key_input;

  while (!over) {
    usleep(DELAY_IN_MICROSECOND);
    getmaxyx(stdscr, screen_height, screen_width);

    key_input = getch();
    switch (key_input) {
      case 'q': {
        over = true;
        break;
      }
      case KEY_UP: {
        if (snake.speed.y == 0) {
          snake.speed.x = 0;
          snake.speed.y = -1;
        }

        break;
      }
      case KEY_DOWN: {
        if (snake.speed.y == 0) {
          snake.speed.x = 0;
          snake.speed.y = 1;
        }

        break;
      }
      case KEY_RIGHT: {
        if (snake.speed.x == 0) {
          snake.speed.x = 2;
          snake.speed.y = 0;
        }

        break;
      }
      case KEY_LEFT: {
        if (snake.speed.x == 0) {
          snake.speed.x = -2;
          snake.speed.y = 0;
        }

        break;
      }
    }

    // snake movement
    for (int i = 0; i < snake.length; i++) {
      snake.last_positions[i] = snake.positions[i];
    }
    for (int i = 0; i < snake.length; i++) {
      if (i == 0) {
        snake.positions[i].x += snake.speed.x;
        snake.positions[i].y += snake.speed.y;
      } else {
        snake.positions[i] = snake.last_positions[i - 1];
      }
    }

    draw();
  }

  endwin();
}

void draw(void) {
  wclear(game_box);

  // box
  box(game_box, 0, 0);

  // snake
  mvwprintw(game_box, snake.positions[0].y, snake.positions[0].x, SNAKE_HEAD);
  for (int i = 1; i < snake.length; i++) {
    int sx = snake.positions[i].x;
    int sy = snake.positions[i].y;
    if (sx != 0 && sy != 0) {
      mvwprintw(game_box, sy, sx, SNAKE_BODY);
    }
  }

  // apple
  mvwprintw(game_box, apple.y, apple.x, APPLE);

  wrefresh(game_box);
}

int rand_int(int min, int max) {
  srand(time(NULL));
  return min + random() % (max - min + 1);
}
