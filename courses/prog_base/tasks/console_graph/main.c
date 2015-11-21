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
double step;

typedef double (*p_func)(double);

double f_val(p_func f, double x) { return f((x+mx) / x_coef) * x_coef + my; }

void put_point(double y, double x) { mvaddch(ceil(y), ceil(x), PLOT_CHAR); }

void draw(p_func f, double l_x, double r_x, int color_pair) {
  attron(COLOR_PAIR(color_pair));
  for (double x = l_x; x < r_x; x += step) {
    double y = f_val(f, x);
    put_point(y, x);
  }
  refresh();
}

double test(double x) { return 1; }

int main(void) {
  int x, y;
  initscr();
  cbreak();
  noecho();
  keypad(stdscr, TRUE);

  start_color();
  init_pair(PLOT_COLOR_1, COLOR_BLACK, COLOR_YELLOW);
  init_pair(PLOT_COLOR_2, COLOR_BLACK, COLOR_BLUE);

  getmaxyx(stdscr, y, x);
  mx = -x / 2;
  my = y / 2;
  x_coef = 3;
  step = 0.2;

  draw(sin, 0, x, PLOT_COLOR_1);
  mx-=3;
  draw(cos, 0, x, PLOT_COLOR_2);

  getchar();
  endwin();

  return 0;
}
