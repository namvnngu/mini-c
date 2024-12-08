#include <ncurses.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>

// The width of two characters horizontally is much closer to the height of
// one character vertically than the width of one character.
// Source: https://stackoverflow.com/a/60046028
#define WIDTH_HEIGHT_TERMINAL_RATIO 2

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
  bool is_over;
} game;
void game_init(void);
void game_loop(void);

struct {
  struct size2 size;
} screen;
void screen_update_size(void);

struct {
  WINDOW *win;
  struct size2 size;
  int border_width;
} map;
void map_init(void);
void map_update(int key_input);
void map_draw(void);
void map_clear(void);
void map_refresh(void);
void map_point_draw(struct vec2 position, int color_pair_id);

struct {
  int length;
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
void apple_generate_position(void);

int random_range(int min, int max);

int main(int argc, char **argv) {
  srand(time(NULL));
  game_init();
  game_loop();
  return 0;
}

void game_init(void) {
  initscr();             // Initialize the screen
  cbreak();              // Disable line buffering
  noecho();              // Don't show typed characters
  curs_set(FALSE);       // Hide the cursor
  keypad(stdscr, TRUE);  // Enable special keys like arrows
  nodelay(stdscr, TRUE); // Enable non-blocking user input
  start_color();         // Enable colors (create colors and color pairs)
  use_default_colors();  // Allow default terminal colors

  game.is_over = false;
  map_init();
  snake_init();
  apple_init();
}
void game_loop(void) {
  while (!game.is_over) {
    int key_input = getch();

    map_clear();
    map_update(key_input);
    map_draw();
    map_refresh();

    usleep(75000);
  }

  endwin();
}

void screen_update_size(void) {
  getmaxyx(stdscr, screen.size.height, screen.size.width);
}

void map_init(void) {
  screen_update_size();
  map.size.width = 25;
  map.size.height = 25;
  map.win =
      newwin(map.size.height, map.size.width * WIDTH_HEIGHT_TERMINAL_RATIO,
             screen.size.height / 2 - map.size.height / 2,
             screen.size.width / 2 -
                 (map.size.width * WIDTH_HEIGHT_TERMINAL_RATIO) / 2);
  map.border_width = 1;
}
void map_update(int key_input) {
  screen_update_size();
  snake_update(key_input);
  apple_update();
}
void map_draw(void) {
  if (game.is_over) {
    return;
  }

  box(map.win, 0, 0);
  snake_draw();
  apple_draw();
}
void map_clear(void) {
  wclear(map.win);
}
void map_refresh(void) {
  wrefresh(map.win);
}
void map_point_draw(struct vec2 position, int color_pair_id) {
  wattron(map.win, COLOR_PAIR(color_pair_id));
  mvwprintw(map.win, position.y, position.x * WIDTH_HEIGHT_TERMINAL_RATIO,
            "  ");
  wattroff(map.win, COLOR_PAIR(color_pair_id));
}

void snake_init(void) {
  struct vec2 *parts =
      malloc(sizeof(struct vec2) * map.size.height * map.size.width);
  if (parts == NULL) {
    fprintf(stderr, "Out of memory.");
    exit(1);
  }

  snake.parts = parts;
  snake.length = 1;
  snake.part_size.width = 1;
  snake.part_size.height = 1;
  snake.parts[0].x = 1;
  snake.parts[0].y = 1;
  snake.direction = EAST;
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
      snake.parts[0].y--;
      break;
    }
    case SOUTH: {
      snake.parts[0].y++;
      break;
    }
    case WEST: {
      snake.parts[0].x--;
      break;
    }
    case EAST: {
      snake.parts[0].x++;
      break;
    }
  }

  if (snake_hit_wall() || snake_hit_itself()) {
    game.is_over = true;
    return;
  }

  if (snake_hit_apple()) {
    snake.length++;
    apple_generate_position();
  }
}
bool snake_hit_wall(void) {
  return snake.parts[0].x <= 0 || snake.parts[0].x >= map.size.width - 1 ||
         snake.parts[0].y <= 0 || snake.parts[0].y >= map.size.height - 1;
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
  for (int i = 0; i < snake.length; i++) {
    if (snake.parts[i].x != 0 && snake.parts[i].y != 0) {
      map_point_draw(snake.parts[i], snake.color_pair_id);
    }
  }
}

void apple_init(void) {
  apple.size.width = 1;
  apple.size.height = 1;
  apple_generate_position();
  apple.color_pair_id = 2;
  init_pair(apple.color_pair_id, -1, COLOR_RED);
}
void apple_update(void) {
}
void apple_draw(void) {
  map_point_draw(apple.position, apple.color_pair_id);
}
void apple_generate_position(void) {
  bool found = false;
  while (!found) {
    apple.position.x =
        random_range(1, map.size.width - map.border_width - apple.size.width);
    apple.position.y =
        random_range(1, map.size.height - map.border_width - apple.size.height);

    bool is_within_snake_body = false;
    for (int i = 0; i < snake.length; i++) {
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
