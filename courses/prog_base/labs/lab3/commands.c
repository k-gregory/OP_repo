#include <curses.h>
#include <stdlib.h>
#include <string.h>

#include "commands.h"
#include "util.h"

int *matrix;
size_t rows, columns;
WINDOW *work_wnd, *display_wnd;

void init_matrix(size_t nrows, size_t ncolumns) {
  rows = nrows;
  columns = ncolumns;
  free(matrix);
  matrix = malloc(nrows * ncolumns * sizeof(int));
}

void print_help(void){
  wprintw(display_wnd, "This is some helpfull shit");
}
