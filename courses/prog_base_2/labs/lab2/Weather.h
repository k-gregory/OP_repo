#pragma once

#define WEATHER_SUNNY (1ul<<0)
#define WEATHER_RAINY (1ul<<1)
#define WEATHER_SNOWY (1ul<<2)
#define WEATHER_WINDY (1ul<<3)

typedef struct Weather{
  unsigned long type;
  float condensation_count;
} Weather;
