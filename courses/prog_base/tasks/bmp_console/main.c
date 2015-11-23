/*BUILDING:
 * gcc main.c -lcurses -std=gnu99
*/

#include <ncurses.h>
#include <stdlib.h>

int max_y, max_x;

void init(void) {
  initscr();
  cbreak();
  noecho();
  keypad(stdscr, TRUE);
  getmaxyx(stdscr, max_y, max_x);
}

int main(void) {
  init();

  getchar();
  endwin();

  return 0;
}
