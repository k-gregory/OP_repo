#include "univ_person.h"
#include "univsec_wicket.h"
#include "univ_term.h"

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define LEN(arr) (sizeof(arr)/sizeof((arr)[0]))

int main(void){
  univ_person* buff[10];
  size_t polled;

  univ_term* t1 = univ_term_new(5,1,UNIV_PERSON_STUDENT);
  univsec_wicket* w1  = univsec_wicket_new();
  univ_person* p = univ_person_new("Kek", UNIV_PERSON_STUDENT);

  univ_term_display(t1);
  polled = univsec_wicket_get_passes(w1, buff, 10);
  printf("0.Polled %zu\n", polled);
  univ_term_send_passers(t1,buff,polled);
  univ_term_display(t1);

  univsec_wicket_pass(w1,p);
  polled = univsec_wicket_get_passes(w1, buff, 10);
  printf("1.Polled %zu\n", polled);
  univ_term_display(t1);

  univsec_wicket_pass(w1,p);
  polled = univsec_wicket_get_passes(w1, buff, 10);
  printf("1.Polled %zu\n", polled);
  univ_term_display(t1);

  univ_person_free(p);
  univ_term_free(t1);
  univsec_wicket_free(w1);
}

int nmain(void){
  char buff[256];
  univ_person* persons[1024];
  size_t n_persons = 0;

  univ_term* t1 = univ_term_new(5,1,UNIV_PERSON_STUDENT);
  univ_term* t2 = univ_term_new(5,2,UNIV_PERSON_STUDENT | UNIV_PERSON_TEACHER);
  univ_term* t3 = univ_term_new(5,3,UNIV_PERSON_SERVICE_STUFF);

  univsec_wicket* w1 = univsec_wicket_new();
  univsec_wicket* w2 = univsec_wicket_new();

  while(1){
    univ_person* p[10];
    size_t n_polled;
    char name_buff[256];
    unsigned int id,cat;

    n_polled = univsec_wicket_get_passes(w1, p, LEN(p));
    printf("%zu polled from 1\n", n_polled);
    univ_term_send_passers(t1, p, n_polled);
    univ_term_send_passers(t2, p, n_polled);
    
    n_polled = univsec_wicket_get_passes(w2,p, LEN(p));
    printf("%zu polled from 2\n", n_polled);
    if(n_polled) printf("FUCK%s IT\n", univ_person_get_name(p[0],NULL, 0));
    univ_term_send_passers(t3, p, n_polled);

    fgets(buff, LEN(buff), stdin);
    if(strcmp(buff,"exit\n") == 0) break;
    else if(sscanf(buff,"pass2 %d %s\n",&cat,name_buff)==2){
      persons[n_persons] = univ_person_new(name_buff, cat);
      univsec_wicket_pass(w2,persons[n_persons++]);
      puts("Passed 2 wicket");
    } else 
    if(sscanf(buff,"pass1 %d %s\n",&cat,name_buff)==2){
      persons[n_persons++] = univ_person_new(name_buff, cat);
      univsec_wicket_pass(w1,persons[n_persons]);
      puts("Passed 1 wicket");
    } 
    else if(strcmp(buff,"disp1\n")==0) univ_term_display(t1);
    else if(strcmp(buff,"disp2\n")==0) univ_term_display(t2);
    univ_term_display(t1);
    univ_term_display(t2);
  }

  for(size_t i = 0; i < n_persons; i++)
    univ_person_free(persons[i]);

  univsec_wicket_free(w1);
  univsec_wicket_free(w2);

  univ_term_free(t1);
  univ_term_free(t2);
  univ_term_free(t3);
}