#include <ncurses.h>

int main(int argc, char **argv) {
  int max_x = 0;
  int max_y = 0;

  // init screen and sets up screen
  initscr();

  // get max width and max height of the screen
  getmaxyx(stdscr, max_y, max_x);

  // create window
  WINDOW *win = newwin(max_y - 2, max_x - 2, 1, 1);
  refresh();

  // make box border
  box(win, 0, 0);

  // move and print in window
  mvwprintw(win, 0, 1, "Snake");
  mvwprintw(win, 1, 1, "#####S @");

  // refreshing the window
  wrefresh(win);

  // pause the screen output
  getch();

  // deallocates memory and ends ncurses
  endwin();

  return 0;
}
