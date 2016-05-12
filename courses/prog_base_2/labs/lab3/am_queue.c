#include "am_queue.h"

#include <stdlib.h>
#include <string.h>

#define INITIAL_CAPACITY (1ul<<4)
#define GROW_FACTOR (2)

struct am_queue {
  size_t capacity;
  size_t contains;

  size_t head;
  size_t tail;

  int* data;
};

am_queue* am_queue_new(){
  am_queue* ret;

  ret = malloc(sizeof(am_queue));
  ret->capacity = INITIAL_CAPACITY;
  ret->contains = 0;
  ret->head = 0;
  ret->tail = 0;
  ret->data = malloc(sizeof(int) * INITIAL_CAPACITY);
  
  return ret;
}

static void am_queue_grow(am_queue* q){
  int* old_data;

  old_data = q->data;
  q->data = malloc(sizeof(int) * q->capacity * GROW_FACTOR);

  if(q->tail < q->head){
    memcpy(q->data, old_data+q->tail, (q->head - q->tail) * sizeof(int));
  } else {
    memcpy(q->data, old_data + q->tail, (q->capacity - q->tail) * sizeof(int));
    memcpy(q->data + q->capacity - q->tail, old_data, q->head * sizeof(int));
  }

  q->tail = 0;
  q->head = q->contains;
  q->capacity *= GROW_FACTOR;

  free(old_data);
}

void am_queue_free(am_queue* q){
  free(q->data);
  free(q);
}

am_queue_status am_queue_add(am_queue* q, int val){
  if(q->contains + 1 == q->capacity)
    am_queue_grow(q);

  q->data[q->head++] = val;
  
  /*TODO: Replace % with bit operations if GROW_FACTOR is 2*/
  q->head %= q->capacity;
  q->contains++;

  return AM_QUEUE_OK;
}

am_queue_status am_queue_remove(am_queue* q){
  if(q->contains == 0) return AM_QUEUE_EMPTY;

  q->tail++;
  /*TODO: Replace % with bit operations if GROW_FACTOR is 2*/  
  q->tail%=q->capacity;
  q->contains--;

  return AM_QUEUE_OK;
}

am_queue_status am_queue_peek(am_queue* q, int* val){
  if(q->contains == 0) return AM_QUEUE_EMPTY;

  *val = q->data[q->tail];
  return AM_QUEUE_OK;
}

size_t am_queue_contains(am_queue* q){
  return q->contains;
}
