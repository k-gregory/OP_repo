#include <ncurses.h>
#include <stdlib.h>

#include "commands.h"
#include "util.h"

#define WORK_HEIGHT 20

typedef void (*command)(char*, char*);

command commands[] ={
  init_matrix
};

void eval(const char* cmd, char* res){

}

WINDOW *work_wnd, *display_wnd;

void init() {
  matrix = NULL;
  initscr();
  nocbreak();
  echo();
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
  init();
  finish();
  return 0;
}
