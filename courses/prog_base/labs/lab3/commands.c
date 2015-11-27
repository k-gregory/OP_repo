#include "commands.h"

extern int* matrix;
extern int rows, columns;
extern WINDOW* work_wnd,*display_wnd,suck;

void init_matrix(size_t nrows,int ncolumns){
  matrix = malloc(sizeof(int)*rows*columns);
  rows=nrows;
  columns=ncolumns;
}
