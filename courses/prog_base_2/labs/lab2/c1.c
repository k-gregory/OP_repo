#include "c.h"

#include <stdlib.h>
#include <stdio.h>

void check(Weather* a, void** state){
  unsigned int *p_sunny_days;
  if(*state == NULL){
    *state = malloc(sizeof(unsigned int));
    
    *((unsigned int*)*state) = 0;
    return;
  }
  if(a == NULL){
    free(*state);
    return;
  }

  if(a->type & WEATHER_SUNNY)
    (*((unsigned int*)*state))++;
  else *((unsigned int*)*state) = 0;

  if(*((unsigned int*)*state) >= 3){
    puts("Still sunny");
    fflush(stdout);
  }
}
