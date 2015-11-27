#include <curses.h>
#include <stdlib.h>
#include <string.h>

#include "commands.h"
#include "util.h"

int *matrix;
size_t rows, columns;
WINDOW *work_wnd, *display_wnd;

void init_matrix(char *cmd, char *res) {
  size_t nrows, ncols;
  if (sscanf(cmd, "init %zu %zu", &nrows, &ncols) != 2)
    if (res != NULL) {
      strcpy(res, "Usage: init %rows %cols");
      return;
    }
  res[0] = 'S';

  matrix = malloc(nrows * ncols * sizeof(int));
}
