#include "univsec_wicket.h"
#include "univ_person.h"

#define UNIVSEC_WICKET_START_STACKSIZE 10

struct univsec_wicket{
  univ_person** passers;
  size_t capacity;
  size_t top;
};

univsec_wicket* univsec_wicket_new(){
  univsec_wicket* ret = malloc(sizeof(struct univsec_wicket));
  ret->passed_top = 0;
  ret->capacity = UNIVSEC_WICKET_START_STACKSIZE;
  ret->passers = malloc(sizeof(univ_person*)*UNIVSEC_WICKET_START_STACKSIZE);
  return ret;
}
void univsec_wicket_free(univsec_wicket* w){
  for(size_t i = 0 ; i < top; i++)
    univsec_person_free(w->passers[i]);
  free(passers);
  free(w);
}

void univsec_wicket_pass(univsec_wicket* w, univ_person* p){
  if(top == capacity){
    
  }
}

size_t univsec_wicket_get_passes(univsec_wicket* w,
				 univ_person** result,
				 size_t max_passes);
