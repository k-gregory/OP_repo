#include <ncurses.h>
#include <stdlib.h>
#include <string.h>

#include "commands.h"
#include "util.h"

#define WORK_HEIGHT 20
#define MAX_CMD_LENGTH 30

typedef void (*command)(char *, char *);

WINDOW *work_wnd, *display_wnd;

void eval(char *cmd) {
  char *af = strchr(cmd, ' ');
  if (af == NULL) {
    if (strcmp(cmd, "help") != 0) {
      wprintw(work_wnd, "Usage: command [args]");
      return;
    } else {
      print_help();
      return;
    }
  }
  *af = '\0';
  if (strcmp(cmd, "help") == 0) {
    print_help();
    return;
  }
}

void init() {
  matrix = NULL;
  initscr();
  nocbreak();
  echo();
  curs_set(0);
  work_wnd = newwin(WORK_HEIGHT, COLS, LINES - WORK_HEIGHT, 0);
  display_wnd = newwin(LINES - WORK_HEIGHT, COLS, 0, COLS);
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

  while (true) {
    int wy, wx;
    getyx(work_wnd, wy, wx);
    wgetstr(work_wnd, cmd_buff);
    if (wy > WORK_HEIGHT - 4)
      wclear(work_wnd);
    eval(cmd_buff);
    waddch(work_wnd, '\n');
    wprintw(work_wnd, "%d %d\n", wy, wx);
    wrefresh(work_wnd);
    wrefresh(display_wnd);
  }
  finish();
  return 0;
}
