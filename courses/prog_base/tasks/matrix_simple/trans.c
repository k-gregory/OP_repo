#include <stdlib.h>

void matrix_copy(int in[4][4], int out[4][4]) {
  for (int i = 0; i < 4; i++)
    for (int j = 0; j < 4; j++)
      out[i][j] = in[i][j];
}

static inline void swap_ints(int *i1, int *i2) {
  int tmp = *i1;
  *i1 = *i2;
  *i2 = tmp;
}

void fillRand(int mat[4][4]) {
  for (int i = 0; i < 4; i++)
    for (int j = 0; j < 4; j++)
      mat[i][j] = (rand() % 2 - 1) * (rand() % 1000);
}

void rotateCCW270(int mat[4][4]) {
  int tmp_mat[4][4];
  for (int i = 0; i < 4; i++)
    for (int j = 0; j < 4; j++)
      tmp_mat[j][4 - i - 1] = mat[i][j];
  matrix_copy(tmp_mat, mat);
}
void flipH(int mat[4][4]) {
  for (int i = 0; i < 4; i++)
    for (int j = 0; j < 4 / 2; j++)
      swap_ints(&mat[i][j], &mat[i][4 - j - 1]);
}
void transposSide(int mat[4][4]) {
  int tmp_mat[4][4];
  for (int i = 0; i < 4; i++)
    for (int j = 0; j < 4; j++)
      tmp_mat[4 - j - 1][4 - i - 1] = mat[i][j];
  matrix_copy(tmp_mat, mat);
}
