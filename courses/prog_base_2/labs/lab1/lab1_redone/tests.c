#include "univ_person_tests.c"
#include "univsec_wicket_tests.c"
#include "univ_term_tests.c"

#include <check.h>
#include <stdlib.h>

int main(void) {
  SRunner *sr;
  int num_failed;

  sr = srunner_create(NULL);

  srunner_add_suite(sr, univ_person_suite());
  srunner_add_suite(sr, univsec_wicket_suite());
  srunner_add_suite(sr, univ_term_suite());

  srunner_run_all(sr, CK_VERBOSE);
  num_failed = srunner_ntests_failed(sr);
  srunner_free(sr);

  return (num_failed == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}
