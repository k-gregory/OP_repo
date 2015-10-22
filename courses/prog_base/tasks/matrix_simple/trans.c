#ifndef __TRANS_C__
#define __TRANS_C__

typedef struct {
  /**
   * Matrix row
   **/
  int m;

  /**
   * Matrix column
   **/
  int n;
} MatrixCoords;

static inline MatrixCoords get_coords_rotated_CCW270(MatrixCoords in) {
  int in_m = in.m;
  int in_n = in.n;
};

void rotateCCW270(int *mat);
void transposSide(int *mat);

#endif
