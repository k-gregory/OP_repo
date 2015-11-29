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

void print_help(void) {
  wprintw(display_wnd,
      "Use \"init rows columns\" to init matrix,\n"\
      "\"randomize min max\" to put random numbers in matrix \n"\
      "\"mutate row col value\" to set value at index \n"\
      "\"null\" to put zeroes in matrix\n"\
      "\"sumDown\" to find sum of els under diagonal \n"\
      "\"reflectSide\" to reflect by main diagonal \n"\
      "\"rotate\" to rotate matrix \n"\
      "\"flipH\" to flip horisontal\n"\
      "\"avg\" to find average value  \n"\
      "\"feswap\" to swap first min and max el-s \n"\
      "\"leswap\" to swap last min and max el-s\n"\
      "\"ecswap\" to swap columns with max and min sum \n"\
      "\"sumC colN\" to find sum of column \n"\
      "\"q\" to quit\n\n"\
      ); 
}

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

long col_sum(size_t column) {
  long sum = 0;
  for (size_t i = 0; i < rows; i++)
    sum += matrix[mi(i, column, columns)];
  return sum;
}

void sumColumn(size_t column) {
  long sum = col_sum(column);
  wprintw(display_wnd, "Sum of column number %zu is %ld\n", column, sum);
  highlited_columns[0] = column;
}

void sumDown() {
  long sum = 0;
  if (columns != rows)
    return;
  for(size_t row = 0;row<rows;row++)
    for(size_t column = 0; column<columns - row;column++)
      sum+=matrix[mi(row,column,columns)];
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

void leswap() {
  size_t min_idx = 0;
  size_t max_idx = 0;
  for (size_t i = 0; i < columns * rows; i++) {
    if (matrix[i] <= matrix[min_idx])
      min_idx = i;
    if (matrix[i] >= matrix[max_idx])
      max_idx = i;
  }
  swap_ints(&matrix[min_idx], &matrix[max_idx]);
  highlited_cells[0] = min_idx;
  highlited_cells[1] = max_idx;
}

void ecswap() {
  size_t min_c = 0;
  size_t max_c = 0;
  for (size_t i = 0; i < columns; i++) {
    if (col_sum(min_c) < col_sum(i))
      min_c = i;
    if (col_sum(max_c) > col_sum(i))
      max_c = i;
  }
  for(size_t i =0;i<rows;i++)
    swap_ints(
	&matrix[mi(i,min_c,columns)],
	&matrix[mi(i,max_c,columns)]
	);
  highlited_columns[0]=min_c;
  highlited_columns[1]=max_c;
}

void tonull(){
  for(size_t i = 0; i<rows*columns;i++)
    matrix[i] = 0;
}

void randomize(int l, int h){
  h++;
  if(h<l)
    swap_ints(&h,&l);
  for(size_t i = 0; i<rows*columns;i++)
    matrix[i] = l + rand()%(h-l);
}

void rotate(){
  if(columns!=rows)
    return;
  int* matrixc = malloc(sizeof(int)*rows*columns);
  for(size_t i = 0; i<rows;i++)
    for(size_t j = 0; j<columns;j++)
      matrixc[mi(rows-j-1,columns-i-1,columns)] = 
	matrix[mi(i,j,columns)];
  memcpy(matrix,matrixc,sizeof(int)*rows*columns);
  free(matrixc);
}
