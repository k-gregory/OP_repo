#pragma once
#include <stdlib.h>

typedef struct am_queue am_queue;

typedef enum am_queue_status {
  AM_QUEUE_OK,
  AM_QUEUE_FULL,
  AM_QUEUE_EMPTY
} am_queue_status;

am_queue* am_queue_new();
void am_queue_free(am_queue* q);

am_queue_status am_queue_add(am_queue* q, int val);
am_queue_status am_queue_remove(am_queue* q);
am_queue_status am_queue_peek(am_queue* q, int* val);
size_t am_queue_contains(am_queue* q);


