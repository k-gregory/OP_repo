#include <ncurses.h>
#include <ImgLib/ImgLib.h>
#include <ImgLib/IL_BMP.h>

#include <stdlib.h>
#include <stdio.h>

int max_y, max_x;

void init(void) {
  initscr();
  cbreak();
  noecho();
  keypad(stdscr, TRUE);
  getmaxyx(stdscr, max_y, max_x);
}

int main(void) {
  il_load_bmp_fromfile("test.bmp");
  return 0;
}
