#include "univ_person.h"
#include <stdlib.h>
#include <string.h>

static univ_person_status univ_person_status_;
#define ok_return(ret)                                                         \
  univ_person_status_ = UNIV_PERSON_S_OK;                                      \
  return ret;

struct univ_person {
  char *name;
  univ_person_category category;
};

univ_person *univ_person_new(const char *name, univ_person_category c) {
  if (name == NULL) {
    univ_person_status_ = UNIV_PERSON_S_BADNAME;
    return NULL;
  }
  univ_person *ret = malloc(sizeof(struct univ_person));
  ret->name = malloc(strlen(name) + 1);
  strcpy(ret->name, name);
  ret->category = c;
  ok_return(ret);
}
void univ_person_free(univ_person *p) {
  free(p->name);
  free(p);
}

char *univ_person_get_name(univ_person *p, char *dest) {
  if (dest == NULL)
    dest = malloc(strlen(p->name) + 1);
  strcpy(dest, p->name);
  ok_return(dest);
}
univ_person_category univ_person_get_category(univ_person *p) {
  ok_return(p->category);
}

univ_person_status univ_person_get_error() { return univ_person_status_; }
