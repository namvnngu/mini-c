#include <ncurses.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>

#define DELAY_IN_MICROSECOND 50000

#define APPLE "  "

#define SNAKE "  "
#define SNAKE_MAX_LENGTH 256

struct vec2 {
  int x;
  int y;
};

enum direction {
  NORTH,
  EAST,
  SOUTH,
  WEST,
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
const char GAME_BOX_MARGIN_INLINE = 50;
const char GAME_BOX_MARGIN_BLOCK = 10;

struct vec2 apple;
const int APPLE_COLOR_PAIR = 1;
const int APPLE_OCCIPED_SPACES = strlen(APPLE);

const int SNAKE_COLOR_PAIR = 2;
const int SNAKE_ABS_X_SPEED = 2;
const int SNAKE_ABS_Y_SPEED = 1;
const int SNAKE_OCCUPIED_SPACES = strlen(SNAKE);
struct {
  struct vec2 positions[SNAKE_MAX_LENGTH];
  struct vec2 last_positions[SNAKE_MAX_LENGTH];
  struct vec2 speed;
  int length;
  enum direction direction;
} snake;

bool over = false;

int main(int argc, char **argv) {
  setup();
  update();
  return 0;
}

void setup(void) {
  srand(time(NULL));

  initscr();
  noecho();
  cbreak();
  curs_set(FALSE);
  keypad(stdscr, TRUE);
  nodelay(stdscr, TRUE);

  start_color();
  use_default_colors();
  init_pair(SNAKE_COLOR_PAIR, -1, COLOR_WHITE);
  init_pair(APPLE_COLOR_PAIR, -1, COLOR_RED);

  getmaxyx(stdscr, screen_height, screen_width);
  game_box_width = screen_width - GAME_BOX_MARGIN_INLINE * 2;
  game_box_height = screen_height - GAME_BOX_MARGIN_BLOCK * 2;
  game_box = newwin(game_box_height, game_box_width, GAME_BOX_MARGIN_BLOCK,
                    GAME_BOX_MARGIN_INLINE);

  apple.x = rand_int(4, game_box_width - 2);
  apple.y = rand_int(4, game_box_height - 2);

  snake.length = 1;
  snake.positions[0].x = SNAKE_OCCUPIED_SPACES;
  snake.positions[0].y = 1;
  snake.speed.x = SNAKE_ABS_X_SPEED;
  snake.speed.y = 0;
  snake.direction = EAST;
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
          snake.speed.y = -SNAKE_ABS_Y_SPEED;
          snake.direction = NORTH;
        }

        break;
      }
      case KEY_DOWN: {
        if (snake.speed.y == 0) {
          snake.speed.x = 0;
          snake.speed.y = SNAKE_ABS_Y_SPEED;
          snake.direction = SOUTH;
        }

        break;
      }
      case KEY_RIGHT: {
        if (snake.speed.x == 0) {
          snake.speed.x = SNAKE_ABS_X_SPEED;
          snake.speed.y = 0;
          snake.direction = EAST;
        }

        break;
      }
      case KEY_LEFT: {
        if (snake.speed.x == 0) {
          snake.speed.x = -SNAKE_ABS_X_SPEED;
          snake.speed.y = 0;
          snake.direction = WEST;
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

    // collision
    bool is_x_collided =
        (snake.speed.x == 0 && snake.positions[0].x == apple.x) ||
        (snake.speed.x > 0 && snake.positions[0].x <= apple.x &&
         apple.x < snake.positions[0].x + snake.speed.x) ||
        (snake.speed.x < 0 && snake.positions[0].x + snake.speed.x < apple.x &&
         apple.x <= snake.positions[0].x);
    bool is_y_collided =
        (snake.speed.y == 0 && snake.positions[0].y == apple.y) ||
        (snake.speed.y > 0 && snake.positions[0].y <= apple.y &&
         apple.y < snake.positions[0].y + snake.speed.y) ||
        (snake.speed.y < 0 && snake.positions[0].y + snake.speed.y < apple.y &&
         apple.y <= snake.positions[0].y);
    if (is_x_collided && is_y_collided) {
      snake.positions[snake.length] = snake.positions[snake.length - 1];
      snake.length += 1;
      apple.x = rand_int(4, game_box_width - 2);
      apple.y = rand_int(4, game_box_height - 2);
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
  wattron(game_box, COLOR_PAIR(SNAKE_COLOR_PAIR));
  for (int i = 0; i < snake.length; i++) {
    int sx = snake.positions[i].x;
    int sy = snake.positions[i].y;
    if (sx != 0 && sy != 0) {
      mvwprintw(game_box, sy, sx, SNAKE);
    }
  }
  wattroff(game_box, COLOR_PAIR(SNAKE_COLOR_PAIR));

  // apple
  wattron(game_box, COLOR_PAIR(APPLE_COLOR_PAIR));
  mvwprintw(game_box, apple.y, apple.x + APPLE_OCCIPED_SPACES, APPLE);
  wattroff(game_box, COLOR_PAIR(APPLE_COLOR_PAIR));

  wrefresh(game_box);
}

int rand_int(int min, int max) {
  return min + rand() % (max - min + 1);
}
