#include <check.h>
#include "trans.h"

int test_matrix[4][4] = {
    {1, 2, 3, 4}, {5, 6, 7, 8}, {9, 10, 11, 12}, {13, 14, 15, 16}

};

/* test_matrix_cw90 == test_matrix_ccw270 */
int test_matrix_cw90[4][4] = {13, 9, 5, 1,  14, 10, 6, 2, 15,
                              11, 7, 3, 16, 12, 8,  4

};

/* test_matrix_cw180 == test_matrix_ccw180 */
int test_matrix_cw180[4][4] = {16, 15, 14, 13, 12, 11, 10, 9, 8,
                               7,  6,  5,  4,  3,  2,  1

};

/* test_matrix_cw270 == test_matrix_ccw90 */
int test_matrix_cw270[4][4] = {4, 8,  12, 16, 3, 7, 11, 15, 2,
                               6, 10, 14, 1,  5, 9, 13

};
int test_matrix_flipH[4][4] = {4,  3,  2, 1,  8,  7,  6, 5, 12,
                               11, 10, 9, 16, 15, 14, 13

};

int test_matrix_flipV[4][4] = {13, 14, 15, 16, 9, 10, 11, 12, 5,
                               6,  7,  8,  1,  2, 3,  4

};

int test_matrix_transMain[4][4] = {1, 5,  9,  13, 2, 6,  10, 14, 3,
                                   7, 11, 15, 4,  8, 12, 16

};

int test_matrix_transSide[4][4] = {16, 12, 8, 4,  15, 11, 7, 3, 14,
                                   10, 6,  2, 13, 9,  5,  1

};

int equals(int m1[4][4], int m2[4][4]) {
  int i, j, n = 4;
  for (i = 0; i < n; i++)
    for (j = 0; j < n; j++)
      if (m1[i][j] != m2[i][j])
        return 0;
  return 1;
}

void matrix_copy(int in[4][4], int out[4][4]) {
  for (int i = 0; i < 4; i++)
    for (int j = 0; j < 4; j++)
      out[i][j] = in[i][j];
}

START_TEST(test_matrix_copy) {
  int buff[4][4];
  matrix_copy(test_matrix, buff);
  ck_assert(equals(test_matrix, buff));
}
END_TEST

START_TEST(test_matrix_equals) { ck_assert(equals(test_matrix, test_matrix)); }
END_TEST
START_TEST(test_matrix_rotate_ccw270_0) {
  int buff[4][4];
  matrix_copy(test_matrix, buff);
  rotateCCW270(buff);
  ck_assert(equals(buff, test_matrix_cw90));
}
END_TEST

START_TEST(test_matrix_flip_h_0) {
  int buff[4][4];
  matrix_copy(test_matrix, buff);
  flipH(buff);
  ck_assert(equals(buff, test_matrix_flipH));
}
END_TEST

START_TEST(test_matrix_transpose_side_0) {
  int buff[4][4];
  matrix_copy(test_matrix, buff);
  transposSide(buff);
  ck_assert(equals(buff, test_matrix_transSide));
}
END_TEST

int main(void) {
  Suite *suite = suite_create("Matrix simple");

  TCase *tcase_base_ops = tcase_create("Basic ops");
  tcase_add_test(tcase_base_ops, test_matrix_equals);
  tcase_add_test(tcase_base_ops, test_matrix_copy);

  TCase *tcase_rotate = tcase_create("Matrix rotate CCW270");
  tcase_add_test(tcase_rotate, test_matrix_rotate_ccw270_0);

  TCase *tcase_flip = tcase_create("Matrix horizontal flip");
  tcase_add_test(tcase_flip, test_matrix_flip_h_0);

  TCase *tcase_transpose = tcase_create("Transpose side");
  tcase_add_test(tcase_transpose, test_matrix_transpose_side_0);

  suite_add_tcase(suite, tcase_base_ops);
  suite_add_tcase(suite, tcase_rotate);
  suite_add_tcase(suite, tcase_flip);
  suite_add_tcase(suite, tcase_transpose);
  SRunner *sr = srunner_create(suite);
  srunner_run_all(sr, CK_VERBOSE);
  int fails = srunner_ntests_failed(sr);
  srunner_free(sr);
  return fails;
}
