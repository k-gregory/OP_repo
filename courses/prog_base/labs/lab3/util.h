#pragma once

extern int *matrix;
extern size_t rows, columns;
extern WINDOW *work_wnd, *display_wnd;

inline int mi(int row, int column, int row_length) {
  return row * row_length + column;
}

#define LEN(arr) (sizeof(arr)/sizeof((arr)[0]))
