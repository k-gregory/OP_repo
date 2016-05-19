#include "am_queue.h"
#include "am_observer.h"

#include <stdlib.h>
#include <stdio.h>
#include <time.h>

typedef struct {
  am_queue *q1;
  am_queue *q2;  
} queues;

typedef struct {
  am_queue *q;
  int num;
} obs_data;

void became_empty_observer(void* _q, void *_od){
  queues* q;
  obs_data* od;
  
  q = _q;
  od = _od;
  
  printf("%p became empty when %d\n",od->q, od->num);
}

void single_over_observer(void* _q, void* _od){
  queues* q;
  obs_data* od;

  q = _q;
  od = _od;

  printf("%p overflow when %d\n", od->q, od->num);
}

void crit_over_observer(void* _q, void* _od){
  queues* q;
  obs_data* od;

  q = _q;
  od = _od;

  printf("%p overflow crit when %d\n", od->q, od->num);
}

int main(void){
  am_queue *q1,*q2;
  queues q_data;
  obs_data d;
  am_observable *empty_observable, *over_observable, * crit_observable;
  size_t i;

  srand(time(NULL));

  empty_observable = am_observable_new();
  am_observable_add_observer(empty_observable, became_empty_observer, &q_data);
  over_observable = am_observable_new();
  am_observable_add_observer(over_observable,single_over_observer, &q_data);  
  crit_observable = am_observable_new();
  am_observable_add_observer(crit_observable, crit_over_observer, &q_data);  
  q1 = am_queue_new();
  q2 = am_queue_new();
  q_data.q1 = q1;
  q_data.q2 = q2;

  for(i = 0; i < 3; i++)
    am_queue_add(q1, rand());
  for(i =0; i < 3; i++)
    am_queue_add(q2, rand());

  while(1){
    int val;
    am_queue* active, *other;

    active = rand() > RAND_MAX/2 ? q1 : q2;
    other = active==q1? q2 : q1;
    val = -RAND_MAX/2 +  rand();

    if(val > 0){
      am_queue_add(active,val);
      if(am_queue_contains(active) == 10){
	d.q = active;
	d.num = val;
	am_observable_emit(over_observable, &d);
	if(am_queue_contains(other) != 9) {
	  int x;
	  am_queue_peek(active, &x);
	  am_queue_remove(active);
	  am_queue_add(other, x);
	} else {
	  am_observable_emit(crit_observable, &d);
	  am_queue_remove(active);
	}
      }
    } else {
      am_queue_remove(active);
      if(!am_queue_contains(active) && am_queue_contains(other) < 2){
	d.q = active;
	d.num = val;
	am_observable_emit(empty_observable, &d);
      } else {
	int x;
	am_queue_peek(other, &x);
	am_queue_remove(other);
	am_queue_add(active, x);
      }
    }
//    printf("%p has %d, %p has %d\n",q1,am_queue_contains(q1),q2,am_queue_contains(q2));
    usleep(250);
  }

  am_queue_free(q1);
  am_queue_free(q2);
  am_observable_free(empty_observable);
  am_observable_free(over_observable);
  am_observable_free(crit_observable);
  exit(EXIT_SUCCESS);
}
