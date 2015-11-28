#include <ncurses.h>
#include <stdlib.h>
#include <string.h>

#include "commands.h"
#include "util.h"

#define WORK_HEIGHT 5
#define MAX_CMD_LENGTH 30

typedef void (*command)(char *, char *);

WINDOW *work_wnd, *display_wnd;

void eval(char *cmd) {
  char *af = strchr(cmd, ' ');
  if (af == NULL) {
    if (strcmp(cmd, "help") != 0) {
      wprintw(work_wnd, "Usage: command [args]\n");
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

  while (true) {
    int wy, wx;
    getyx(work_wnd, wy, wx);
    wgetstr(work_wnd, cmd_buff);
    wclear(display_wnd);
    if (wy > WORK_HEIGHT - 2)
      wclear(work_wnd);
    eval(cmd_buff);

    wrefresh(display_wnd);
    wrefresh(work_wnd);
  }
  finish();
  return 0;
}
