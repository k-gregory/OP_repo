#include "WeatherQueue.h"
#include <dlfcn.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void print_weather(Weather w){
  printf("%d %lf\n",w.type,w.condensation_count);
}

typedef void (*check_f)(Weather* w,void** state);

int main(void){
  char checker_selection;
  void* checker_state;
  void* checker_lib;
  check_f check_cb;
  WeatherQueue* q;
  Weather w;
  size_t i;

  q = weather_queue_new();
  checker_state = NULL;

  puts("Choose library[0/1]");
  fflush(stdout);
  checker_selection = getchar();
  getchar();
  switch(checker_selection){
  case '0':
    checker_lib = dlopen("./libc0.so",RTLD_LOCAL|RTLD_LAZY);
    break;
  case '1':
    checker_lib = dlopen("./libc1.so",RTLD_LOCAL|RTLD_LAZY);
    break;
  default:
    fputs("Can't get your selection", stderr);
    exit(EXIT_FAILURE);
  }
  if((check_cb = dlsym(checker_lib,"check")) == NULL){
    fputs("Can't load lib", stderr);
    exit(EXIT_FAILURE);
  }
  check_cb(NULL,&checker_state);
  
  while(1){
    char buff[10];

    puts("Enter weather type");
    fflush(stdout);
    fgets(buff,10,stdin);
    if(sscanf(buff,"%lu\n",&(w.type))!=1) continue;

    puts("Enter condensation");
    fflush(stdout);
    fgets(buff,10,stdin);
    if(sscanf(buff,"%f",&(w.condensation_count))!=1) continue;

    weather_queue_enqueue(q,&w);
    check_cb(&w,&checker_state);
  }
  
  weather_queue_free(q);
  dlclose(checker_lib);
}
