#include <ncurses.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>

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

void map_init(void);
void map_update(void);
void map_draw(void);

void snake_init(void);
void snake_update(int key_input);
bool snake_hit_wall(void);
bool snake_hit_itself(void);
bool snake_hit_apple(void);
void snake_draw(void);

void apple_init(void);
void apple_update(void);
void apple_draw(void);
void apple_generate(void);

int random_range(int min, int max);

int screen_width = 0;
int screen_height = 0;

struct {
  WINDOW *win;
  struct vec2 position;
  int width;
  int height;
  int border_width;
} map;

struct {
  struct vec2 position;
  char *presentation;
  int color_pair_id;
} apple;

struct {
  int length;
  struct vec2 *parts;
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

  map_init();
  snake_init();
  apple_init();
}
void game_loop(void) {
  bool is_over = false;
  while (!is_over) {
    wclear(map.win);

    int key_input = getch();

    map_update();
    snake_update(key_input);
    apple_update();

    if (snake_hit_wall() || snake_hit_itself()) {
      is_over = true;
      continue;
    }

    map_draw();
    snake_draw();
    apple_draw();

    wrefresh(map.win);

    usleep(DELAY_IN_MICROSECOND);
  }

  endwin();
}

void map_init(void) {
  getmaxyx(stdscr, screen_height, screen_width);
  map.width = 50;
  map.height = 25;
  map.position.x = screen_width / 2 - map.width / 2;
  map.position.y = screen_height / 2 - map.height / 2;
  map.win = newwin(map.height, map.width, map.position.y, map.position.x);
  map.border_width = 1;
}
void map_update(void) {
  getmaxyx(stdscr, screen_height, screen_width);
}
void map_draw(void) {
  box(map.win, 0, 0); // Drawer border
}

void snake_init(void) {
  struct vec2 *parts = malloc(sizeof(struct vec2) * map.height * map.width);
  if (parts == NULL) {
    fprintf(stderr, "Out of memory.");
    exit(1);
  }

  snake.parts = parts;
  snake.length = 1;
  snake.parts[0].x = 1;
  snake.parts[0].y = 1;
  snake.single_part_presentation = "  ";
  snake.direction = EAST;
  snake.abs_speed.x = strlen(snake.single_part_presentation);
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
    apple_generate();
  }
}
bool snake_hit_wall(void) {
  return snake.parts[0].x <= 0 || snake.parts[0].x >= map.width - 1 ||
         snake.parts[0].y <= 0 || snake.parts[0].y >= map.height - 1;
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
  wattron(map.win, COLOR_PAIR(snake.color_pair_id));
  for (int i = 0; i < snake.length; i++) {
    int sx = snake.parts[i].x;
    int sy = snake.parts[i].y;
    if (sx != 0 && sy != 0) {
      mvwprintw(map.win, sy, sx, snake.single_part_presentation);
    }
  }
  wattroff(map.win, COLOR_PAIR(snake.color_pair_id));
}

void apple_init(void) {
  apple.presentation = "  ";
  apple_generate();
  apple.color_pair_id = 2;
  init_pair(apple.color_pair_id, -1, COLOR_RED);
}
void apple_update(void) {
}
void apple_draw(void) {
  wattron(map.win, COLOR_PAIR(apple.color_pair_id));
  mvwprintw(map.win, apple.position.y, apple.position.x, apple.presentation);
  wattroff(map.win, COLOR_PAIR(apple.color_pair_id));
}
void apple_generate(void) {
  bool found = false;
  while (!found) {
    int apple_width = strlen(apple.presentation);
    int apple_height = 1;
    apple.position.x =
        random_range(1, map.width - map.border_width - apple_width);
    apple.position.y =
        random_range(1, map.height - map.border_width - apple_height);

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
