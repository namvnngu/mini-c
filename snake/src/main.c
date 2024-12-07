#include <ncurses.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>

#define APPLE "  "
#define SNAKE "  "
#define WALL_WIDTH 50
#define WALL_HEIGHT 25
#define DELAY_IN_MICROSECOND 75000

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

void game_setup(void);
void game_loop(void);

void wall_init(void);
void wall_update(void);
void wall_draw(void);

void snake_init(void);
void snake_update(int key_input);
void snake_draw(void);

void apple_init(void);
void apple_update(void);
void apple_draw(void);
void apple_generate(void);

int random_range(int min, int max);

int screen_width = 0;
int screen_height = 0;

WINDOW *wall;
const int ROW_COLUMN_RATIO = 2;

struct {
  struct vec2 position;
} apple;
const int APPLE_COLOR_PAIR_ID = 1;
const int APPLE_OCCIPED_SPACES = strlen(APPLE);

const int SNAKE_COLOR_PAIR_ID = 2;
const int SNAKE_ABS_X_SPEED = 2;
const int SNAKE_ABS_Y_SPEED = 1;
const int SNAKE_OCCUPIED_SPACES = strlen(SNAKE);
struct {
  int length;
  struct vec2 body[WALL_WIDTH * WALL_HEIGHT];
  enum direction direction;
} snake;

int main(int argc, char **argv) {
  game_setup();
  game_loop();
  return 0;
}

void game_setup(void) {
  srand(time(NULL)); // Seed random number generator

  initscr();             // Initialize the screen
  cbreak();              // Disable line buffering
  noecho();              // Don't show typed characters
  curs_set(FALSE);       // Hide the cursor
  keypad(stdscr, TRUE);  // Enable special keys like arrows
  nodelay(stdscr, TRUE); // Enable non-blocking user input

  start_color();
  use_default_colors();

  wall_init();
  snake_init();
  apple_init();
}
void game_loop(void) {
  bool is_over = false;
  while (!is_over) {
    wclear(wall);

    int key_input = getch();

    wall_update();
    snake_update(key_input);
    apple_update();

    wall_draw();
    snake_draw();
    apple_draw();

    wrefresh(wall);

    usleep(DELAY_IN_MICROSECOND);
  }

  endwin();
}

void wall_init(void) {
  getmaxyx(stdscr, screen_height, screen_width);
  wall = newwin(WALL_HEIGHT, WALL_WIDTH, 0, 0);
}
void wall_update(void) {
  getmaxyx(stdscr, screen_height, screen_width);
}
void wall_draw(void) {
  box(wall, 0, 0);
}

void snake_init(void) {
  init_pair(SNAKE_COLOR_PAIR_ID, -1, COLOR_WHITE);
  snake.length = 1;
  snake.body[0].x = SNAKE_OCCUPIED_SPACES;
  snake.body[0].y = 1;
  snake.direction = EAST;
}
void snake_update(int key_input) {
  for (int i = snake.length - 1; i > 0; i--) {
    snake.body[i] = snake.body[i - 1];
  }

  switch (key_input) {
    case KEY_UP: {
      if (snake.direction != SOUTH) {
        snake.direction = NORTH;
      }
      break;
    }
    case KEY_DOWN: {
      if (snake.direction != NORTH) {
        snake.direction = SOUTH;
      }
      break;
    }
    case KEY_RIGHT: {
      if (snake.direction != WEST) {
        snake.direction = EAST;
      }
      break;
    }
    case KEY_LEFT: {
      if (snake.direction != EAST) {
        snake.direction = WEST;
      }
      break;
    }
  }

  switch (snake.direction) {
    case NORTH: {
      snake.body[0].y -= SNAKE_ABS_Y_SPEED;
      break;
    }
    case SOUTH: {
      snake.body[0].y += SNAKE_ABS_Y_SPEED;
      break;
    }
    case EAST: {
      snake.body[0].x += SNAKE_ABS_X_SPEED;
      break;
    }
    case WEST: {
      snake.body[0].x -= SNAKE_ABS_X_SPEED;
      break;
    }
  }
}
void snake_draw(void) {
  wattron(wall, COLOR_PAIR(SNAKE_COLOR_PAIR_ID));
  for (int i = 0; i < snake.length; i++) {
    int sx = snake.body[i].x;
    int sy = snake.body[i].y;
    if (sx != 0 && sy != 0) {
      mvwprintw(wall, sy, sx, SNAKE);
    }
  }
  wattroff(wall, COLOR_PAIR(SNAKE_COLOR_PAIR_ID));
}

void apple_init(void) {
  init_pair(APPLE_COLOR_PAIR_ID, -1, COLOR_RED);
  apple_generate();
}
void apple_update(void) {
}
void apple_draw(void) {
  wattron(wall, COLOR_PAIR(APPLE_COLOR_PAIR_ID));
  mvwprintw(wall, apple.position.y, apple.position.x + APPLE_OCCIPED_SPACES,
            APPLE);
  wattroff(wall, COLOR_PAIR(APPLE_COLOR_PAIR_ID));
}
void apple_generate(void) {
  apple.position.x = random_range(1, WALL_WIDTH - 3);
  apple.position.y = random_range(1, WALL_HEIGHT - 1);
}

int random_range(int min, int max) {
  return min + rand() % (max - min + 1);
}
