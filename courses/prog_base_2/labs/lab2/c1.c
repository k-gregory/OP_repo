#include "c.h"

#include <stdlib.h>
#include <stdio.h>

typedef struct week_weather {
  double conds[7];
  int pos;
} week_weather;

void check(Weather* a, void** state){
  week_weather* ww;
  float accum;
  size_t i;
  if(*state == NULL){
    *state = malloc(sizeof(week_weather));
    ww = *state;
    ww->pos = 0;
    for(i = 0; i < 7; i++)
      ww->conds[i] = 0;
    return;
  }
  if(a == NULL){
    free(*state);
    return;
  }

  ww = *state;

  ww->conds[ww->pos++] = a->condensation_count;
  ww->pos%=7;

  accum = 0;
  for(i =0; i < 7; i++)
    accum+=ww->conds[i];

  if(accum > 40){
    puts("Much rain");
    fflush(stdout);
  }
}
