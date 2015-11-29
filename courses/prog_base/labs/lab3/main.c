#include <ncurses.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

#include "commands.h"
#include "util.h"

#define WORK_HEIGHT 8
#define MAX_CMD_LENGTH 30

typedef void (*command)(char *, char *);

WINDOW *work_wnd, *display_wnd;

void finish();
void eval(char *cmd) {
  if (cmd[0] == '\0')
    return;
  char *af = strchr(cmd, ' ');
  if (af != NULL)
    *af = '\0';
  if (strcmp(cmd, "init") == 0) {
    int r, c;
    if (af != NULL)
      if (sscanf(af + 1, "%d %d", &r, &c) == 2) {
        init_matrix(r, c);
        return;
      }

    wprintw(work_wnd, "Usage: init nrows ncolumns\n");
    return;
  }
  if (strcmp(cmd, "randomize") == 0) {
    int l, h;
    if (af != NULL)
      if (sscanf(af + 1, "%d %d", &l, &h) == 2) {
        randomize(l, h);
        return;
      }

    wprintw(work_wnd, "Usage: randomize min max\n");
    return;
  }
  if (strcmp(cmd, "mutate") == 0) {
    int r, c, nv;
    if (af != NULL)
      if (sscanf(af + 1, "%d %d %d", &r, &c, &nv) == 3) {
        mutate(r, c, nv);
        return;
      }
    wprintw(work_wnd, "Usage: mutate row column new_value\n");
    return;
  }
  if (strcmp(cmd, "null") == 0) {
    tonull();
    return;
  }
  if (strcmp(cmd, "sumDown") == 0) {
    sumDown();
    return;
  }
  if (strcmp(cmd, "reflectSide") == 0) {
    transposeSide();
    return;
  }
  if (strcmp(cmd, "rotate") == 0) {
    rotate();
    return;
  }
  if (strcmp(cmd, "flipH") == 0) {
    flipH();
    return;
  }
  if (strcmp(cmd, "avg") == 0) {
    avg();
    return;
  }
  if (strcmp(cmd, "feswap") == 0) {
    feswap();
    return;
  }
  if (strcmp(cmd, "leswap") == 0) {
    leswap();
    return;
  }
  if (strcmp(cmd, "ecswap") == 0) {
    ecswap();
    return;
  }
  if (strcmp(cmd, "q") == 0) {
    finish();
    exit(EXIT_SUCCESS);
    return;
  }
  if (strcmp(cmd, "sumC") == 0) {
    size_t column;
    if (af != NULL)
      if (sscanf(af + 1, "%zu", &column) == 1) {
        sumColumn(column);
        return;
      }
    wprintw(work_wnd, "Usage: sumC column\n");
    return;
  }
  print_help();
}

void init() {
  matrix = NULL;
  initscr();
  srand(time(NULL));
  nocbreak();
  echo();
  curs_set(1);
  start_color();
  init_pair(COLUMN_HIGHLIGHT, COLOR_BLUE, COLOR_YELLOW);
  init_pair(CELL_HIGHLIGHT, COLOR_BLUE, COLOR_RED);
  work_wnd = newwin(WORK_HEIGHT, COLS, LINES - WORK_HEIGHT, 0);
  display_wnd = newwin(LINES - WORK_HEIGHT, COLS, 0, 0);
}

void finish(void) {
  delwin(work_wnd);
  delwin(display_wnd);
  endwin();
  free(matrix);
}

int main(void) {
  char cmd_buff[MAX_CMD_LENGTH];
  init();

  init_matrix(4, 4);
  print_help();
  display_matrix();
  wrefresh(display_wnd);
  while (true) {
    int wy, wx;
    getyx(work_wnd, wy, wx);
    wgetstr(work_wnd, cmd_buff);
    wclear(display_wnd);
    wborder(display_wnd,'|','|','=','=','*','*','*','*');
    if (wy > WORK_HEIGHT - 3)
      wclear(work_wnd);
    eval(cmd_buff);
    if (matrix != NULL)
      display_matrix();

    wrefresh(display_wnd);
    wrefresh(work_wnd);
  }
  finish();
  return 0;
}
