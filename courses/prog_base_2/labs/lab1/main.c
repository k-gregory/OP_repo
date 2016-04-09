#include "univ_person.h"
#include "univsec_wicket.h"
#include "univ_term.h"

#include <stdlib.h>
#include <stdio.h>

#define LEN(arr) (sizeof(arr)/sizeof((arr)[0]))


int main(void){
  char buff[256];

  univ_term* t1 = univ_term_new(5,1,UNIV_PERSON_STUDENT);
  univ_term* t2 = univ_term_new(5,2,UNIV_PERSON_STUDENT | UNIV_PERSON_TEACHER);
  univ_term* t3 = univ_term_new(5,3,UNIV_PERSON_SERVICE_STUFF);

  univsec_wicket* w1 = univsec_wicket_new();
  univsec_wicket* w2 = univsec_wicket_new();

  while(1){
    char name_buff[256];
    unsigned int id,cat;
    fgets(buff, LEN(buff), stdin);
    if(strcmp(buff,"exit")) break;
    if(sscanf(buff,"pass %u \n")==1){

    }
  }

  univsec_wicket_free(w1);
  univsec_wicket_free(w2);

  univ_term_free(t1);
  univ_term_free(t2);
  univ_term_free(t3);
}
