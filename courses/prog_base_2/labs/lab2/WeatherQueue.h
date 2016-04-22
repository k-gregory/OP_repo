#pragma once

#include "Weather.h"

typedef struct WeatherQueue WeatherQueue;

typedef enum WeatherQueueStatus {
  WEATHER_QUEUE_OK,
  ERR_WEATHER_QUEUE_EMPTY,
} WeatherQueueStatus;

WeatherQueue* weather_queue_new(void);
void weather_queue_free(WeatherQueue* q);

WeatherQueueStatus weather_queue_enqueue(WeatherQueue* q, Weather* w);
WeatherQueueStatus weather_queue_peek(WeatherQueue* q,Weather* out);
WeatherQueueStatus weather_queue_dequeue(WeatherQueue* q);


