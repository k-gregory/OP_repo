#include <stdlib.h>
#include <stdio.h>
#include <limits.h>
#include <time.h>

typedef struct LLISN { //LinkedListIntStackNode
  int val;
  struct LLISN* prev;
} LLISN;

typedef struct LListIntStack {
  LLISN* last;
} LListIntStack;

void init_llist_int_stack(LListIntStack* s) {
  s->last = NULL;
}

void deinit_llist_int_stack(LListIntStack* s){
  LLISN* node = s->last;
  while(node!=NULL) {
    LLISN* next_node = node->prev;
    free(node);
    node = next_node;
  }
  s->last = NULL;
}

void push_llist_int_stack(LListIntStack* s, int val){
  LLISN* new_node = malloc(sizeof(LLISN));
  new_node->val = val;
  new_node->prev = s->last;
  s->last = new_node;
}

int pop_llist_int_stack(LListIntStack* s){
  LLISN* rem = s->last;
  int ret = rem->val;
  s->last = rem->prev;
  free(rem);
  return ret;
}

typedef struct ArrayIntStack {
  int head; //New elements will be added here
  int capacity;
  int* hld; //Data holding array
} ArrayIntStack;


void init_array_int_stack(ArrayIntStack *s, int initialCapacity) {
  s->head = 0;
  s->hld = malloc(sizeof(int) * initialCapacity);
  s->capacity = initialCapacity;
}

void deinit_array_int_stack(ArrayIntStack *s) { free(s->hld); }

void grow_array_int_stack(ArrayIntStack *s) {
  s->capacity = s->capacity * 2 + 1;
  s->hld = realloc(s->hld, s->capacity * sizeof(int));
}

void push_array_int_stack(ArrayIntStack* s, int el){
  if(s->capacity==s->head)
    grow_array_int_stack(s);
  s->hld[s->head++] = el;
}

int pop_array_int_stack(ArrayIntStack* s){
  if(s->head==0)
    return INT_MIN;
  return s->hld[s->head--];
}


int main(int argc, char* argv[]) {
  float startTime,endTime;
#ifdef ARRAY
  ArrayIntStack as;
  init_array_int_stack(&as, 10);
  for(size_t i = argc; i<1000000;i++)
    push_array_int_stack(&as,i); 

  startTime = (float)clock()/CLOCKS_PER_SEC;
  int res = 0;
  for(size_t i = 0; i<1000000;i+=2)
    res=pop_array_int_stack(&as)-pop_array_int_stack(&as);
  endTime = (float)clock()/CLOCKS_PER_SEC;
  deinit_array_int_stack(&as);

  printf("ArrayIntStack: %f, res:%d", endTime-startTime, res);
#endif
#ifdef LIST

#endif
  return EXIT_SUCCESS;
}
