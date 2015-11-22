/*BUILDING:
 * gcc main.c -lcurses -std=gnu99
 */
#include <ncurses.h>
#include <stdlib.h>
#include <tgmath.h>

#define PLOT_CHAR ' '
#define PLOT_COLOR_1 1
#define PLOT_COLOR_2 2
#define DECART_COLOR 3

double x_coef;
int mx, my;
int max_y, max_x;
double step;

typedef double (*p_func)(double);

double f_val(p_func f, double x) { return f((x + mx) / x_coef) * x_coef - my; }

static inline int get_x(double x) { return nearbyint(x); }
static inline int get_y(double y) { return max_y - nearbyint(y); }

void pput_s(int y, int x) { mvaddch(y, x, PLOT_CHAR); }

void connect(int y1, int x1, int y2, int x2) {
  pput_s(y1, x1);
  pput_s(y2, x2);
  if (x1 == 0)
    return;
  for (int y = fmin(y1, y2); y < fmax(y1, y2); y++)
    pput_s(y, x1);
}

void draw(p_func f, double l_x, double r_x, int color_pair) {
  attron(COLOR_PAIR(color_pair));
  double prev_x = l_x;
  double prev_y = f(l_x);
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

static inline double dec_x(double x){
  return (x+mx)/x_coef;
}
static inline double dec_y(double y){
  return (max_y-y+my)/x_coef;
}

void draw_decart() {
  attron(COLOR_PAIR(DECART_COLOR));
  for (int y = 0; y < max_y; y++) {
    mvaddch(y,max_x/2,'|');
  }
  for(int y= 1;y<max_y;y+=max_y/5){
    mvprintw(y,max_x/2-2,"%.2lf",dec_y(y));
  }
  for (int x = 0; x < max_x; x++) {
    mvaddch(max_y/2,x,'-');
  }
  for(int x = 1; x<max_x;x+=max_x/5){
    mvprintw(max_y/2+2,x-2,"%.2lf",dec_x(x));
    mvaddch(max_y/2,x,'*');
  }
}

double f1(double x) { return x * x - 5; }

double f2(double x) { return 0.5 * tan(x + 2); }

void init() {
  initscr();
  cbreak();
  noecho();
  keypad(stdscr, TRUE);

  start_color();
  init_pair(PLOT_COLOR_1, COLOR_BLACK, COLOR_YELLOW);
  init_pair(PLOT_COLOR_2, COLOR_BLACK, COLOR_BLUE);
  init_pair(DECART_COLOR, COLOR_BLACK, COLOR_RED);

  getmaxyx(stdscr, max_y, max_x);
  mx = -max_x / 2;
  my = -max_y / 2;
  x_coef = 1;
  step = 0.01;
}

int main(void) {
  puts("Use arrows to move plot\nUse + or -  and = or _ to scale plot");
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
      x_coef *= 1.05;
      break;
    case '-':
      x_coef /= 1.05;
      break;
    case '_':
      x_coef *= 0.7;
      break;
    case '+':
      x_coef /= 0.7;
      break;
    }
    if (x_coef <= 0)
      x_coef = 0.01;
    clear();
    draw(f2, 0, max_x, PLOT_COLOR_2);
    draw(f1, 0, max_x, PLOT_COLOR_1);
    draw_decart();
  } while ((key = getch()) != 'q');

  endwin();

  return 0;
}
