#include <curses.h>
#include <stdlib.h>
#include <string.h>
#include "commands.h"
#include "util.h"

int *matrix;
size_t rows, columns;
WINDOW *work_wnd, *display_wnd;

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
}

void print_help(void) { wprintw(display_wnd, "This is some helpfull shit\n"); }

void display_matrix() {
  for (size_t i = 0; i < rows; i++) {
    for (size_t j = 0; j < columns; j++)
      wprintw(display_wnd, "%02d ", matrix[mi(i, j, columns)]);
    wprintw(display_wnd, "\n");
  }
}

void free_matrix() {
  free(matrix);
  matrix = calloc(rows * columns, sizeof(int));
}

void mutate(size_t row, size_t column, int new_value) {
  matrix[mi(row, column, columns)] = new_value;
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
  for (size_t column = 0; column < columns; column++)
    for (size_t row = column; row < columns; row++)
      swap_ints(&matrix[mi(row, column, columns)],
                &matrix[mi(column, row, columns)]);
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
}
