#pragma once 

#include <stdlib.h>

typedef struct _Stack {
  size_t length;
  size_t pos;
  int* values;
} Stack;

Stack* alloc_Stack(int capacity);
void free_Stack(Stack* s);

void push(Stack* s, int value);
int pop(Stack* s);
void print_Stack(Stack* s);
