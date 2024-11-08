#include <ncurses.h>
#include <stdbool.h>
#include <unistd.h>

#define DELAY_IN_MICROSECOND 50000

int main(int argc, char **argv) {
  int screen_width = 0;
  int screen_height = 0;
  int margin = 5;

  initscr();
  getmaxyx(stdscr, screen_height, screen_width);
  noecho();
  cbreak();
  curs_set(FALSE);
  nodelay(stdscr, TRUE);

  WINDOW *win = newwin(screen_height - margin * 2, screen_width - margin * 2,
                       margin, margin);
  box(win, 0, 0);

  char ch;
  bool exit = false;

  while (!exit) {
    getmaxyx(stdscr, screen_height, screen_width);

    ch = getch();

    switch (ch) {
      case 'q': {
        exit = true;
        break;
      }
    }

    mvwprintw(win, 2, 1, "#######>");
    mvwprintw(win, 10, 20, "@");

    wrefresh(win);
    usleep(DELAY_IN_MICROSECOND);
  }

  endwin();

  return 0;
}
