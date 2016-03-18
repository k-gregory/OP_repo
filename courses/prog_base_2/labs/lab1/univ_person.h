#pragma once

typedef struct univ_person univ_person;

typedef enum univ_person_category {
  UNIV_PERSON_STUDENT,
  UNIV_PERSON_TEACHER,
  UNIV_PERSON_SERVICE_STUFF,
  UNIV_PERSON_UNKNOWN,
  UNIV_PERSON_SPECIAL
} univ_person_category;

univ_person* univ_person_new(const char* name, univ_person_category c);
void univ_person_free(univ_person* p);

const char* univ_person_get_name(univ_person* p);
univ_person_category univ_person_get_category(univ_person* p);

