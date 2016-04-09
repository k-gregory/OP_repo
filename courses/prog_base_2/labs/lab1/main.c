#include "univ_person.h"
#include "univ_term.h"

#include <stdlib.h>
#include <stdio.h>

#define LEN(arr) (sizeof(arr)/sizeof((arr)[0]))

int main(void){
  char name_buff[20];
  univ_person* passers[10];
  univ_term* term  = univ_term_new(20,4,UNIV_PERSON_TEACHER);
  for(size_t i = 0; i < LEN(passers); i++){
    sprintf(name_buff,"P%zu",i);
    passers[i] = univ_person_new(name_buff, UNIV_PERSON_TEACHER);
  }
  univ_term_send_passers(term,passers, 10);
  univ_term_display(term);
  univ_term_send_passers(term,passers, 2);
  univ_term_display(term);
  univ_term_send_passers(term,passers+4, 3);
  univ_term_send_passers(term,passers,1);
  univ_term_display(term);
  univ_term_send_passers(term,passers, 10);
  univ_term_display(term);

  for(size_t i = 0; i < LEN(passers); i++){
    univ_person_free(passers[i]);
  }
  univ_term_free(term);
}
