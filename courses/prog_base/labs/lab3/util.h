#pragma once

#include <stdlib.h>

extern int *matrix;
extern size_t rows, columns;
extern WINDOW *work_wnd, *display_wnd;

static inline size_t mi(size_t row, size_t column, size_t row_length) {
  return row * row_length + column;
}

#define LEN(arr) (sizeof(arr) / sizeof((arr)[0]))

#define COLUMN_HIGHLIGHT 1

#define CELL_HIGHLIGHT 2
