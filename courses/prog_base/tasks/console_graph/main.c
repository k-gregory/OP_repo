/*BUILDING:
 * gcc main.c -lcurses -std=gnu99
 */

#include <ncurses.h>
#include <unistd.h>
#include <stdlib.h>
#include <math.h>

#define PLOT_CHAR ' '
#define PLOT_COLOR_1 1
#define PLOT_COLOR_2 2

double x_coef;
int mx, my;
int max_y, max_x;
double step;

typedef double (*p_func)(double);

double f_val(p_func f, double x) { return f((x + mx) / x_coef) * x_coef - my; }

static inline int get_x(double x) { return nearbyint(x); }
static inline int get_y(double y) { return max_y - nearbyint(y); }

void put_point(double y, double x) { mvaddch(get_y(y), get_x(x), PLOT_CHAR); }

void draw(p_func f, double l_x, double r_x, int color_pair) {
  attron(COLOR_PAIR(color_pair));
  for (double x = l_x; x < r_x; x += step) {
    double y = f_val(f, x);
    if (isnan(y))
      continue;
    put_point(y, x);
  }
  refresh();
}

void init() {
  initscr();
  cbreak();
  noecho();
  keypad(stdscr, TRUE);

  start_color();
  init_pair(PLOT_COLOR_1, COLOR_BLACK, COLOR_YELLOW);
  init_pair(PLOT_COLOR_2, COLOR_BLACK, COLOR_BLUE);

  getmaxyx(stdscr, max_y, max_x);
  mx = -max_x / 2;
  my = -max_y / 2;
  x_coef = 3;
  step = 0.02;
}

int main(void) {
  init();
  int key = 0;
  do {
    switch (key) {
    case KEY_UP:
      my += 5;
      break;
    case KEY_DOWN:
      my -= 5;
      break;
    case KEY_LEFT:
      mx -= 5;
      break;
    case KEY_RIGHT:
      mx += 5;
      break;
    }
    clear();
    draw(sin, 0, max_x, PLOT_COLOR_1);
    draw(cos, 0, max_x, PLOT_COLOR_2);
    draw(sqrt, 0, max_x, PLOT_COLOR_1);
  } while ((key = getch()) != 'q');

  endwin();

  return 0;
}
