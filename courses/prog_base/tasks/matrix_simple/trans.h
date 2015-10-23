#ifndef __TRANS_H__
#define __TRANS_H__

void matrix_copy(int in[4][4], int out[4][4]);
void fillRand(int mat[4][4]);
void rotateCCW270(int mat[4][4]);
void flipH(int mat[4][4]);
void transposSide(int mat[4][4]);

#endif
