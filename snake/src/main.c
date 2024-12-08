#include <ncurses.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>

#define DELAY_IN_MICROSECOND 75000
#define CELL_WIDTH 2
#define CELL_HEIGHT 1

struct vec2 {
  int x;
  int y;
};

struct size2 {
  int width;
  int height;
};

enum direction {
  NORTH,
  EAST,
  SOUTH,
  WEST,
};

struct {
  struct size2 size;
} screen;

void game_setup(void);
void game_loop(void);

struct {
  WINDOW *win;
  struct vec2 position;
  struct size2 size;
  int border_width;
} map;
void map_init(void);
void map_update(void);
void map_draw(void);

struct {
  int parts_length;
  struct vec2 *parts;
  struct size2 part_size;
  enum direction direction;
  int color_pair_id;
} snake;
void snake_init(void);
void snake_update(int key_input);
bool snake_hit_wall(void);
bool snake_hit_itself(void);
bool snake_hit_apple(void);
void snake_draw(void);

struct {
  struct vec2 position;
  struct size2 size;
  int color_pair_id;
} apple;
void apple_init(void);
void apple_update(void);
void apple_draw(void);
void apple_generate(void);

int random_range(int min, int max);

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
  getmaxyx(stdscr, screen.size.height, screen.size.width);
  map.size.width = 50;
  map.size.height = 25;
  map.position.x = screen.size.width / 2 - map.size.width / 2;
  map.position.y = screen.size.height / 2 - map.size.height / 2;
  map.win =
      newwin(map.size.height, map.size.width, map.position.y, map.position.x);
  map.border_width = 1;
}
void map_update(void) {
  getmaxyx(stdscr, screen.size.height, screen.size.width);
}
void map_draw(void) {
  box(map.win, 0, 0); // Drawer border
}

void snake_init(void) {
  struct vec2 *parts =
      malloc(sizeof(struct vec2) * map.size.height * map.size.width);
  if (parts == NULL) {
    fprintf(stderr, "Out of memory.");
    exit(1);
  }

  snake.parts = parts;
  snake.parts_length = 1;
  snake.part_size.width = 1;
  snake.part_size.height = 1;
  snake.parts[0].x = 1;
  snake.parts[0].y = 1;
  snake.direction = EAST;
  snake.color_pair_id = 1;
  init_pair(snake.color_pair_id, -1, COLOR_BLUE);
}
void snake_update(int key_input) {
  for (int i = snake.parts_length - 1; i > 0; i--) {
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
      snake.parts[0].y -= snake.part_size.height * CELL_HEIGHT;
      break;
    }
    case SOUTH: {
      snake.parts[0].y += snake.part_size.height * CELL_HEIGHT;
      break;
    }
    case EAST: {
      snake.parts[0].x += snake.part_size.width * CELL_WIDTH;
      break;
    }
    case WEST: {
      snake.parts[0].x -= snake.part_size.width * CELL_WIDTH;
      break;
    }
  }

  if (snake_hit_apple()) {
    snake.parts_length++;
    apple_generate();
  }
}
bool snake_hit_wall(void) {
  return snake.parts[0].x <= 0 || snake.parts[0].x >= map.size.width - 1 ||
         snake.parts[0].y <= 0 || snake.parts[0].y >= map.size.height - 1;
}
bool snake_hit_itself(void) {
  for (int i = 1; i < snake.parts_length; i++) {
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
  for (int i = 0; i < snake.parts_length; i++) {
    int sx = snake.parts[i].x;
    int sy = snake.parts[i].y;
    if (sx != 0 && sy != 0) {
      mvwprintw(map.win, sy, sx, "  ");
    }
  }
  wattroff(map.win, COLOR_PAIR(snake.color_pair_id));
}

void apple_init(void) {
  apple_generate();
  apple.size.width = 1;
  apple.size.height = 1;
  apple.color_pair_id = 2;
  init_pair(apple.color_pair_id, -1, COLOR_RED);
}
void apple_update(void) {
}
void apple_draw(void) {
  wattron(map.win, COLOR_PAIR(apple.color_pair_id));
  mvwprintw(map.win, apple.position.y, apple.position.x, "  ");
  wattroff(map.win, COLOR_PAIR(apple.color_pair_id));
}
void apple_generate(void) {
  bool found = false;
  while (!found) {
    apple.position.x = random_range(1, map.size.width - map.border_width -
                                           apple.size.width * CELL_WIDTH);
    apple.position.y = random_range(1, map.size.height - map.border_width -
                                           apple.size.height * CELL_HEIGHT);

    if ((apple.position.x % 2) != (snake.parts[0].x % 2)) {
      continue;
    }

    bool is_within_snake_body = false;
    for (int i = 0; i < snake.parts_length; i++) {
      if (snake.parts[i].x == apple.position.x &&
          snake.parts[i].y == apple.position.y) {
        is_within_snake_body = true;
      }
    }
    if (is_within_snake_body) {
      continue;
    }

    found = true;
  }
}

int random_range(int min, int max) {
  return min + rand() % (max - min + 1);
}
