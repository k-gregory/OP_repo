#include "univ_person.h"
#include <stdlib.h>
#include <string.h>

struct univ_person {
  char* name;
  univ_person_category category;
};

univ_person* univ_person_new(const char* name, univ_person_category c){
  univ_person* ret = malloc(sizeof(struct univ_person));
  ret->name = malloc(strlen(name));
  strcpy(ret->name, name);
  ret->category = c;
  return ret;
}
void univ_person_free(univ_person* p){
  free(p->name);
  free(p);
}

const char* univ_person_get_name(univ_person* p){
  return p->name;
}
univ_person_category univ_person_get_category(univ_person* p){
  return p->category;
}
