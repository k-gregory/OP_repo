#pragma once

#include <stdlib.h>

void init_matrix(size_t rows, size_t columns);
void print_help(void);
void display_matrix();
void mutate(size_t row, size_t column, int new_value);
void flipH();
void transposeSide();
void avg();
void sumColumn(size_t column);
void sumDown();
void feswap();
void leswap();
void ecswap();
void randomize(int l, int h);
void tonull();
void rotate();
void sumDown();
