#pragma once

typedef struct univ_person univ_person;

typedef enum {
  UNIV_PERSON_S_OK,
  UNIV_PERSON_S_BADNAME,
} univ_person_status;

typedef enum univ_person_category {
  UNIV_PERSON_STUDENT,
  UNIV_PERSON_TEACHER,
  UNIV_PERSON_SERVICE_STUFF,
  UNIV_PERSON_UNKNOWN,
  UNIV_PERSON_SPECIAL
} univ_person_category;

univ_person* univ_person_new(const char* name, univ_person_category c);
void univ_person_free(univ_person* p);

char* univ_person_get_name(univ_person* p, char* dest);
univ_person_category univ_person_get_category(univ_person* p);

univ_person_status univ_person_get_error(); //FIXME: Thread-safety sucks
