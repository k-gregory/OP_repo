#include <ncurses.h>
#include <stdlib.h>

#include "util.h"

#define WORK_HEIGHT 20

int* matrix=NULL;
int rows,columns;
WINDOW* work_wnd, *display_wnd;

void init() {
  initscr();
  nocbreak();
  echo();
//  keypad(stdscr, TRUE);

//  start_color();
  
  work_wnd = newwin(WORK_HEIGHT,COLS,LINES-WORK_HEIGHT,0);
  display_wnd = newwin(LINES-WORK_HEIGHT,COLS,0,COLS);

}

void finish(void){
  delwin(work_wnd);
  delwin(display_wnd);
  endwin();
  free(matrix);
}

int main(void) {
  init();
  WINDOW* t = newwin(10,10,10,10);
  wprintw(t,"loh");
  wrefresh(t);
  while(true){
  wprintw(work_wnd,"sosi");
  refresh();
  };
  wprintw(display_wnd,"suka");
  wrefresh(work_wnd);
  wrefresh(display_wnd);
  getchar();

  finish();
  return 0;
}
