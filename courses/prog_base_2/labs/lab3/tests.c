#include "am_queue_tests.c"

#include <check.h>
#include <stdlib.h>

int main(void){
  SRunner *sr;
  int num_failed;

  sr = srunner_create(NULL);

  srunner_add_suite(sr,am_queue_suite());

  srunner_run_all(sr, CK_VERBOSE);
  num_failed  = srunner_ntests_failed(sr);
  srunner_free(sr);

  return (num_failed == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}
