#include "Stack.h"

#include <stdio.h>

Stack* alloc_Stack(int capacity){
  if(capacity==0)
    capacity = 10;
  Stack* s = malloc(sizeof(Stack));
  s->values = malloc(sizeof(int)*capacity);
  s->length = capacity;
  s->pos = 0;
  return s;
}

void free_Stack(Stack* s){
  free(s->values);
  free(s);
}

void push(Stack* s, int value){
  if(s->pos==s->length-1){
    s->values = realloc(s->values,sizeof(int)*(s->length*2+1));
    s->length = s->length*2+1;
  }
  s->values[s->pos++] = value;
}
int pop(Stack* s){
  return s->values[--(s->pos)];
}
void print_Stack(Stack* s){
  for(int i = 0; i< s->pos;i++)
    printf("%d ", s->values[i]);
  putchar('\n');
}
