#include "am_observer.h"
#include <stdlib.h>

#define INITIAL_CAPACITY (1ul<<2)
#define GROW_FACTOR 2

typedef struct am_observer{
  void* data;
  am_observable_cb h;
} am_observer;

struct am_observable{
  size_t capacity;
  size_t top;

  am_observer *observers;
};

am_observable* am_observable_new(){
  am_observable* ret;

  ret  = malloc(sizeof(am_observable));
  ret->capacity = INITIAL_CAPACITY;
  ret->top = 0;
  ret->observers = malloc(sizeof(am_observer) * ret->capacity);

  return ret;
}

void am_observable_emit(am_observable* o, void* event){
  size_t i;
  for(i = 0; i < o->top; i++)
    o->observers[i].h(o->observers[i].data, event);
}

void am_observable_add_observer
(am_observable* o, am_observable_cb h, void* data){
  if(o->capacity <= o->top){
    o->capacity*=GROW_FACTOR;
    o->observers = realloc(o->observers, sizeof(am_observer) * o->capacity);
  }

  o->observers[o->top].data = data;
  o->observers[o->top].h = h;
  
  o->top++;
}

void am_observable_remove_observer
(am_observable* o, am_observable_cb h, void* data){
  size_t i,j;
  for(i = 0; i < o->top; i++){
    if(o->observers[i].h == h && o->observers[i].data==data){
      for(j = i; j < o->top - 1; j++)
	o->observers[j] = o->observers[j + 1];
      break;
    }
  }

  o->top--;
}

void am_observable_free(am_observable* o){
  free(o->observers);
  free(o);
}
