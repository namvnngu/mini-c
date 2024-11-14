#include <ncurses.h>
#include <stdbool.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

#define DELAY_IN_MICROSECOND 75000

void setup(void);
void loop(void);

int rand_int(int min, int max);

enum snake_direction {
  up,
  down,
  right,
  left,
};

int screen_width = 0;
int screen_height = 0;

WINDOW *sbox;
int sbox_width;
int sbox_height;
const char SBOX_MARGIN_INLINE = 15;
const char SBOX_MARGIN_BLOCK = 5;

int apple_x;
int apple_y;
const char APPLE = '@';

int snake_x;
int snake_y;
const char SNAKE_HEAD = '$';
const char SNAKE_BODY = '*';

int main(int argc, char **argv) {
  setup();
  loop();
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
  sbox_width = screen_width - SBOX_MARGIN_INLINE * 2;
  sbox_height = screen_height - SBOX_MARGIN_BLOCK * 2;
  sbox = newwin(sbox_height, sbox_width, SBOX_MARGIN_BLOCK, SBOX_MARGIN_INLINE);

  apple_x = rand_int(4, sbox_width - 2);
  apple_y = rand_int(4, sbox_height - 2);

  snake_x = 2;
  snake_y = 2;
}

void loop(void) {
  int key_input;

  enum snake_direction snake_dir = right;

  bool exit = false;

  while (!exit) {
    getmaxyx(stdscr, screen_height, screen_width);
    box(sbox, 0, 0);

    key_input = getch();
    switch (key_input) {
      case 'q': {
        exit = true;
        break;
      }
      case KEY_UP: {
        snake_dir = up;
        break;
      }
      case KEY_DOWN: {
        snake_dir = down;
        break;
      }
      case KEY_RIGHT: {
        snake_dir = right;
        break;
      }
      case KEY_LEFT: {
        snake_dir = left;
        break;
      }
    }

    switch (snake_dir) {
      case up: {
        snake_y--;
        break;
      }
      case down: {
        snake_y++;
        break;
      }
      case right: {
        snake_x++;
        break;
      }
      case left: {
        snake_x--;
        break;
      }
    }
    mvwprintw(sbox, snake_y, snake_x, "****$");

    mvwprintw(sbox, apple_y, apple_x, "%c", APPLE);

    wrefresh(sbox);
    usleep(DELAY_IN_MICROSECOND);
    wclear(sbox);
  }
  endwin();
}

int rand_int(int min, int max) {
  srand(time(NULL));
  return min + random() % (max - min + 1);
}
