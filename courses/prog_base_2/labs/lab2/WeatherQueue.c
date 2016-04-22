#include "WeatherQueue.h"

#include "Weather.h"

#include <stdlib.h>
#include <string.h>

#define INITIAL_WEATHER_QUEUE_CAPACITY (1ul<<4)

struct WeatherQueue {
  Weather *data;
  size_t capacity;
  size_t contains;

  size_t tail;
  size_t head;
};

WeatherQueue* weather_queue_new(void){
  WeatherQueue* ret;
  ret = malloc(sizeof(WeatherQueue));
  
  ret->capacity = INITIAL_WEATHER_QUEUE_CAPACITY;
  ret->data = malloc(sizeof(Weather) * INITIAL_WEATHER_QUEUE_CAPACITY);
  ret->contains = 0;
  ret->tail = 0;
  ret->head = 0;
  
  return ret;
}

void weather_queue_free(WeatherQueue* q){
  free(q->data);
  free(q);
}

static void weather_queue_grow(WeatherQueue* q){
  Weather* old_data;

  old_data = q->data;
  q->data = malloc(sizeof(Weather) * q->capacity * 2);

  if(q->tail < q->head) {
    memcpy(q->data, old_data + q->tail, (q->head - q->tail)*sizeof(Weather));
  } else {
    memcpy(q->data, old_data + q->tail, (q->capacity - q->tail)*sizeof(Weather));
    memcpy(q->data + q->capacity - q->tail, old_data, q->head*sizeof(Weather));
  }

  q->tail = 0;
  q->head = q->contains;
  q->capacity*= 2;

  free(old_data);
}

WeatherQueueStatus weather_queue_enqueue(WeatherQueue* q, Weather* w){
  if(q->contains + 1 == q->capacity)
    weather_queue_grow(q);

  q->data[q->head++] = *w;
  q->head %= q->capacity;
  q->contains++;
}

WeatherQueueStatus weather_queue_peek(WeatherQueue* q, Weather* out){
  if(q->contains == 0) return ERR_WEATHER_QUEUE_EMPTY;

  *out= q->data[q->tail];

  return WEATHER_QUEUE_OK;
}

WeatherQueueStatus weather_queue_dequeue(WeatherQueue* q){
  if(q->contains == 0) return ERR_WEATHER_QUEUE_EMPTY;

  q->tail++;
  
  q->tail %= q->capacity;
  q->contains--;
  
  return WEATHER_QUEUE_OK;
}

