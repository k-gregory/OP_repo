#include <curses.h>
#include <stdlib.h>
#include <string.h>
#include "commands.h"
#include "util.h"

int *matrix;
size_t rows, columns;
WINDOW *work_wnd, *display_wnd;

size_t highlited_cells[2];
size_t highlited_columns[2];

void swap_ints(int *a, int *b) {
  int t = *a;
  *a = *b;
  *b = t;
}

void init_matrix(size_t nrows, size_t ncolumns) {
  rows = nrows;
  columns = ncolumns;
  free(matrix);
  matrix = malloc(nrows * ncolumns * sizeof(int));
  for (size_t i = 0; i < rows * columns; i++)
    matrix[i] = rand() % 100;
  highlited_cells[0] = mi(rows, 0, columns);
  highlited_cells[1] = mi(rows, 0, columns);
  highlited_columns[0] = columns;
  highlited_columns[1] = columns;
}

void print_help(void) { wprintw(display_wnd, "This is some helpfull shit\n"); }

void display_matrix() {
  attron(COLOR_PAIR(COLUMN_HIGHLIGHT));
  for (size_t i = 0; i < rows; i++) {
    for (size_t j = 0; j < columns; j++) {
      if (j == highlited_columns[0] || j == highlited_columns[1])
        wattron(display_wnd, COLOR_PAIR(COLUMN_HIGHLIGHT));
      if (mi(i, j, columns) == highlited_cells[0] ||
          mi(i, j, columns) == highlited_cells[1])
        wattron(display_wnd, COLOR_PAIR(CELL_HIGHLIGHT));
      wprintw(display_wnd, "%02d ", matrix[mi(i, j, columns)]);
      wattroff(display_wnd, COLOR_PAIR(COLUMN_HIGHLIGHT));
      wattroff(display_wnd, COLOR_PAIR(CELL_HIGHLIGHT));
    }
    wprintw(display_wnd, "\n");
  }
  highlited_cells[0] = mi(rows, 0, columns);
  highlited_cells[1] = mi(rows, 0, columns);
  highlited_columns[0] = columns;
  highlited_columns[1] = columns;
}

void free_matrix() {
  free(matrix);
  matrix = calloc(rows * columns, sizeof(int));
}

void mutate(size_t row, size_t column, int new_value) {
  highlited_cells[0] = mi(row, column, columns);
  matrix[mi(row, column, columns)] = new_value;
}

void flipV() {
  for (size_t i = 0; i < rows; i++)
    for (size_t j = 0; j < columns / 2; j++)
      swap_ints(&matrix[mi(i, j, columns)],
                &matrix[mi(i, columns - j, columns)]);
}

void flipH() {
  for (size_t i = 0; i < rows / 2; i++)
    for (size_t j = 0; j < columns; j++)
      swap_ints(&matrix[mi(i, j, columns)],
                &matrix[mi(rows - i - 1, j, columns)]);
}

void transposeSide() {
  if (rows != columns)
    return;
  for (size_t row = 0; row < rows; row++)
    for (size_t column = 0; column < rows - row; column++)
      swap_ints(&matrix[mi(row, column, columns)],
                &matrix[mi(rows - column - 1, columns - row - 1, columns)]);
}

void avg() {
  double avg = 0;
  for (size_t i = 0; i < columns * rows; i++)
    avg += matrix[i];
  avg /= columns * rows;
  wprintw(display_wnd, "Average of matrix:%lf\n", avg);
}

void sumColumn(size_t column) {
  long sum = 0;
  for (size_t i = 0; i < rows; i++)
    sum += matrix[mi(i, column, columns)];
  wprintw(display_wnd, "Sum of column number %zu is %ld\n", column, sum);
  highlited_columns[0] = column;
}

void sumDown() {
  long sum = 0;
  if (columns != rows)
    return;
  for (size_t column = 0; column < columns; column++)
    for (size_t row = column; row < columns; row++)
      sum += matrix[mi(row, column, columns)];
  wprintw(display_wnd, "Sum of el-s under main diagonal is %ld\n", sum);
}

void feswap() {
  size_t min_idx = 0;
  size_t max_idx = 0;
  for (size_t i = 0; i < columns * rows; i++) {
    if (matrix[i] < matrix[min_idx])
      min_idx = i;
    if (matrix[i] > matrix[max_idx])
      max_idx = i;
  }
  swap_ints(&matrix[min_idx], &matrix[max_idx]);
  highlited_cells[0] = min_idx;
  highlited_cells[1] = max_idx;
}

void leswap() {}
