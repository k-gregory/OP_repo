#pragma once

#include <time.h>

#define CAR_MAX_MANUFACTURER_NAME_LENGTH 30
#define CAR_MAX_MODEL_NAME_LENGTH 30

typedef struct Car {
  char manufacturer[CAR_MAX_MANUFACTURER_NAME_LENGTH];
  char model[CAR_MAX_MODEL_NAME_LENGTH];
} Car;
typedef struct Driver {
  Car c;
  double averageSpeedKm;
  double kmFare;
  int satisfiedClients;
  int unsatisfiedClients;
  time_t hired_at;
} Student;

int driver_parse_from_xml_file(Driver* d, const char* filename);
