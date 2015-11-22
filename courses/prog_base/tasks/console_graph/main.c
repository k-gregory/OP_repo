/*BUILDING:
 * gcc main.c -lcurses -std=gnu99
 */

#include <ncurses.h>
#include <assert.h>
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


void connect(int y1, int x1, int y2, int x2) {
  mvaddch(y1, x1, PLOT_CHAR);
  mvaddch(y2, x2, PLOT_CHAR);
   if(x1==x2){
     for(int y = y1+1;y<y2;y++)
       mvaddch(y,x1,PLOT_CHAR);
     return;
   }
  if(y1<y2){
    for(int y = y1;y<y2;y++)
      mvaddch(y,x2,PLOT_CHAR);
  }
  if (y1 > y2) {
    for (int y = y2 - 1; y < y1; y++)
      mvaddch(y, x1, PLOT_CHAR);
  }
}

void draw(p_func f, double l_x, double r_x, int color_pair) {
  attron(COLOR_PAIR(color_pair));
  int prev_x = get_x(l_x);
  int prev_y = get_y(f(l_x));
  for (double x = l_x; x < r_x; x += step) {
    double y = f_val(f, x);
    if (isnan(y))
      continue;
    connect(get_y(prev_y), get_x(prev_x), get_y(y), get_x(x));
    prev_x = x;
    prev_y = y;
  }
  refresh();
}

double f1(double x) { return x * x - 5; }

double f2(double x) { return tan(x * x) + sin(2 * x) * sin(2 * x); }

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
  puts("Use arrows to move plot\n Use + or -  and = or _ to scale plot");
  getchar();
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
    case '=':
      x_coef *= 1.15;
      break;
    case '-':
      x_coef /= 1.15;
      break;
    case '+':
      x_coef += 1;
      break;
    case '_':
      x_coef -= 1;
      break;
    }
    if (x_coef <= 0)
      x_coef = 0.01;
    clear();

    draw(f2, 0, max_x, PLOT_COLOR_2);
    draw(f1, 0, max_x, PLOT_COLOR_1);
  } while ((key = getch()) != 'q');

  endwin();

  return 0;
}
