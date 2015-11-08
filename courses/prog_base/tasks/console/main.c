/*BUILDING:
 * gcc main.c -lcurses -std=gnu99
*/

#include <ncurses.h>
#include <unistd.h>
#include <stdlib.h>

#define BLUE_PAIR 1
#define CYAN_PAIR 2
#define GREEN_PAIR 3

static inline int get_pattern(int y, int x) {
  switch (x % 3) {
  case 0:
    return BLUE_PAIR;
    break;
  case 1:
    return CYAN_PAIR;
    break;
  case 2:
    return GREEN_PAIR;
    break;
  };
  return BLUE_PAIR;
}

static inline int isInRange(int y, int x, int height, int width) {
  if (y < 0 || y >= height)
    return 0;
  if (x < 0 || x >= width)
    return 0;
  return 1;
}

void draw(int height, int width) {
  for (int x = -height; x <= width; x++) {
    for (int y = 0; y <= height; y++) {
      int dx = x + y;
      int dy = y;
      if (abs(x) % 2 == 0) {
        dy = height - y;
        dx = x + dy;
      }
      if (isInRange(dy, dx, height, width)) {
        attron(COLOR_PAIR(get_pattern(dy, dx)));
        mvaddch(dy, dx, '*');
        refresh();
        usleep(5000);
      }
    };
  }
}

int main(void) {
  int x,y;
  initscr();
  cbreak();
  noecho();
  keypad(stdscr, TRUE);
  start_color();


  init_pair(BLUE_PAIR, COLOR_BLACK, COLOR_BLUE);
  init_pair(CYAN_PAIR, COLOR_BLACK, COLOR_CYAN);
  init_pair(GREEN_PAIR, COLOR_BLACK, COLOR_GREEN);

  getmaxyx(stdscr,y,x);
  draw(y,x);
  getchar();

  endwin();

  return 0;
}
