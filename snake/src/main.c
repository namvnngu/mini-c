#include <ncurses.h>
#include <stdbool.h>
#include <unistd.h>

#define DELAY_IN_MICROSECOND 75000

int main(int argc, char **argv) {

  initscr();
  noecho();
  cbreak();
  curs_set(FALSE);
  keypad(stdscr, TRUE);
  nodelay(stdscr, TRUE);

  int screen_width = 0;
  int screen_height = 0;
  getmaxyx(stdscr, screen_height, screen_width);

  int WIN_MARGIN_INLINE = 15;
  int WIN_MARGIN_BLOCK = 5;
  WINDOW *win = newwin(screen_height - WIN_MARGIN_BLOCK * 2,
                       screen_width - WIN_MARGIN_INLINE * 2, WIN_MARGIN_BLOCK, WIN_MARGIN_INLINE);

  int key_input;

  int snake_x = 0;
  int snake_y = 2;

  bool exit = false;

  while (!exit) {
    getmaxyx(stdscr, screen_height, screen_width);
    box(win, 0, 0);

    key_input = getch();
    switch (key_input) {
      case 'q': {
        exit = true;
        break;
      }
      case KEY_RIGHT: {
        break;
      }
      case KEY_LEFT: {
        break;
      }
      case KEY_DOWN: {
        break;
      }
      case KEY_UP: {
        break;
      }
    }

    snake_x++;
    mvwprintw(win, snake_y, snake_x, "#######>");

    mvwprintw(win, 10, 20, "@");

    wrefresh(win);
    usleep(DELAY_IN_MICROSECOND);
    wclear(win);
  }

  endwin();

  return 0;
}
