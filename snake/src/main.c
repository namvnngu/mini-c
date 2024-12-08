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
bool snake_hit_wall(void);
bool snake_hit_itself(void);
bool snake_hit_apple(void);
void snake_draw(void);

void apple_init(void);
void apple_update(void);
void apple_draw(void);
void apple_random_position(void);

int random_range(int min, int max);

int screen_width = 0;
int screen_height = 0;

WINDOW *wall;

struct {
  struct vec2 position;
  char *presentation;
  int color_pair_id;
} apple;

struct {
  int length;
  struct vec2 parts[WALL_WIDTH * WALL_HEIGHT];
  char *single_part_presentation;
  enum direction direction;
  struct vec2 abs_speed;
  int color_pair_id;
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
  start_color();         // Enable colors (create colors and color pairs)
  use_default_colors();  // Allow default terminal colors

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

    if (snake_hit_wall() || snake_hit_itself()) {
      is_over = true;
      continue;
    }

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
  wall = newwin(WALL_HEIGHT, WALL_WIDTH, screen_height / 2 - WALL_HEIGHT / 2,
                screen_width / 2 - WALL_WIDTH / 2);
}
void wall_update(void) {
  getmaxyx(stdscr, screen_height, screen_width);
}
void wall_draw(void) {
  box(wall, 0, 0);
}

void snake_init(void) {
  snake.length = 1;
  snake.parts[0].x = 1;
  snake.parts[0].y = 1;
  snake.single_part_presentation = "  ";
  snake.direction = EAST;
  snake.abs_speed.x = 2;
  snake.abs_speed.y = 1;
  snake.color_pair_id = 1;
  init_pair(snake.color_pair_id, -1, COLOR_BLUE);
}
void snake_update(int key_input) {
  for (int i = snake.length - 1; i > 0; i--) {
    snake.parts[i] = snake.parts[i - 1];
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
      snake.parts[0].y -= snake.abs_speed.y;
      break;
    }
    case SOUTH: {
      snake.parts[0].y += snake.abs_speed.y;
      break;
    }
    case EAST: {
      snake.parts[0].x += snake.abs_speed.x;
      break;
    }
    case WEST: {
      snake.parts[0].x -= snake.abs_speed.x;
      break;
    }
  }

  if (snake_hit_apple()) {
    snake.length++;
    apple_random_position();
  }
}
bool snake_hit_wall(void) {
  return snake.parts[0].x <= 0 || snake.parts[0].x >= WALL_WIDTH - 1 ||
         snake.parts[0].y <= 0 || snake.parts[0].y >= WALL_HEIGHT - 1;
}
bool snake_hit_itself(void) {
  for (int i = 1; i < snake.length; i++) {
    if (snake.parts[i].x == snake.parts[0].x &&
        snake.parts[i].y == snake.parts[0].y) {
      return true;
    }
  }
  return false;
}
bool snake_hit_apple(void) {
  return snake.parts[0].x == apple.position.x &&
         snake.parts[0].y == apple.position.y;
}
void snake_draw(void) {
  wattron(wall, COLOR_PAIR(snake.color_pair_id));
  for (int i = 0; i < snake.length; i++) {
    int sx = snake.parts[i].x;
    int sy = snake.parts[i].y;
    if (sx != 0 && sy != 0) {
      mvwprintw(wall, sy, sx, SNAKE);
    }
  }
  wattroff(wall, COLOR_PAIR(snake.color_pair_id));
}

void apple_init(void) {
  apple.presentation = "  ";
  apple_random_position();
  apple.color_pair_id = 2;
  init_pair(apple.color_pair_id, -1, COLOR_RED);
}
void apple_update(void) {
}
void apple_draw(void) {
  wattron(wall, COLOR_PAIR(apple.color_pair_id));
  mvwprintw(wall, apple.position.y, apple.position.x, APPLE);
  wattroff(wall, COLOR_PAIR(apple.color_pair_id));
}
void apple_random_position(void) {
  bool found = false;
  while (!found) {
    int apple_width = strlen(apple.presentation);
    // Subtract apple width and border width
    apple.position.x = random_range(1, WALL_WIDTH - apple_width - 1);
    // Subtract apple height and border width
    apple.position.y = random_range(1, WALL_HEIGHT - 1 - 1);

    if ((apple.position.x % 2) != (snake.parts[0].x % 2)) {
      continue;
    }

    bool is_with_snake_body = false;
    for (int i = 0; i < snake.length; i++) {
      if (snake.parts[i].x == apple.position.x &&
          snake.parts[i].y == apple.position.y) {
        is_with_snake_body = true;
      }
    }
    if (is_with_snake_body) {
      continue;
    }

    found = true;
  }
}

int random_range(int min, int max) {
  return min + rand() % (max - min + 1);
}
