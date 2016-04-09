#include "univ_term.h"

#include "univ_person.h"
#include <stdlib.h>
#include <stdio.h>

#define UNIV_TERM_MEMORY 20

static univ_term_status univ_term_status_;
#define ok_return(ret)				\
  univ_term_status_ = UNIV_TERM_S_OK;		\
  return ret;

univ_term_status univ_term_get_error(){
  return univ_term_status_;
}

struct univ_term {
  univ_person* passers[UNIV_TERM_MEMORY];
  unsigned int n_passers;
  unsigned int n_output;
  unsigned int term_number;
  univ_person_category categories;
};

#define MY_MIN(a,b) ((a)<(b) ? (a) : (b))
#define MY_MAX(a,b) ((a)>(b) ? (a) : (b))

univ_term* univ_term_new(unsigned int output_number,
			 unsigned int term_number,
			 univ_person_category c){
  if(output_number > UNIV_TERM_MAX_OUTPUT_NUMBER){
    univ_term_status_ = UNIV_TERM_S_TOOMANY_OUTPUT;
    return NULL;
  }
  univ_term* ret = malloc(sizeof(univ_term));
  
  ret->n_passers = 0;
  ret->n_output = output_number;
  ret->term_number = term_number;
  ret->categories = c;
    
  ok_return(ret);
}

void univ_term_free(univ_term* t){
  free(t);
}

void univ_term_set_categories(univ_term* t,univ_person_category c){
  t->categories = c;
}

#define UNIV_TERM_CATEGORY_CASE(x) case x : return #x; break
static const char* univ_term_category_repr(univ_person_category c){
  switch(c){
        UNIV_TERM_CATEGORY_CASE(UNIV_PERSON_STUDENT);
	UNIV_TERM_CATEGORY_CASE(UNIV_PERSON_TEACHER);
	UNIV_TERM_CATEGORY_CASE(UNIV_PERSON_SERVICE_STUFF);
	UNIV_TERM_CATEGORY_CASE(UNIV_PERSON_UNKNOWN);
	UNIV_TERM_CATEGORY_CASE(UNIV_PERSON_SPECIAL);
  default:
    return "Bad category!";
  }
}
void univ_term_display(univ_term* t){
  printf("Term %d displays passers:\n", t->term_number);
  size_t displayed = 0;
  for(size_t i = 0;
      i < t->n_passers && displayed < t->n_output;
      i++){
    univ_person* passer = t->passers[i];
    univ_person_category c = univ_person_get_category(passer);
    if((c & t->categories) == 0) continue;
    char* name = univ_person_get_name(passer, NULL, 0);
    printf("%s passed he is %s\n",
	   name,
	   univ_term_category_repr(univ_person_get_category(passer)));
    
    displayed++;
    free(name);
  }
}

void univ_term_set_output_number(univ_term* t, unsigned int n){
  if(n > UNIV_TERM_MAX_OUTPUT_NUMBER){
    univ_term_status_ = UNIV_TERM_S_TOOMANY_OUTPUT;
    return;
  }
  t->n_output = n;
}



void univ_term_send_passers(univ_term* t,
			    univ_person **passers_arr,
			    size_t len){
  size_t lost;
  if(len == 0) return;
  
  len = MY_MIN(UNIV_TERM_MEMORY, len);
  if(t->n_passers + len < UNIV_TERM_MEMORY)
    lost = 0;
  else lost = t->n_passers + len - UNIV_TERM_MEMORY;
  
  for(int i = t->n_passers - lost - 1; i >= 0; i--){
    t->passers[i + len] = t->passers[i];
  }

  for(size_t i = 0; i < len; i++)
    t->passers[i] = passers_arr[i];
  
  t->n_passers += len - lost;
}
