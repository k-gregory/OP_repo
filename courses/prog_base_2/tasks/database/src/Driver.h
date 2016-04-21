#pragma once

#include <time.h>
#include <sqlite3.h>

typedef struct Driver{
    sqlite3_int64 id;

    char* name;
    char* surname;

    char* car_manufacturer;
    char* car_model;
    double car_average_speed;

    double km_fare;
    unsigned int satisfied_clients;
    unsigned int unsatisfied_clients;

    time_t hired_at;
} Driver;

Driver* driver_create(char* name,
                      char* surname,

                      char* car_manufacturer,
                      char* car_model,
                      double car_average_speed,

                      double km_fare,

                      unsigned int satisfied_clients,
                      unsigned int unsatisfied_clients,

                      time_t hired_at);

typedef enum SaveStatus {
    SAVE_OK,
    SAVE_FAIL
} SaveStatus;

SaveStatus driver_save(sqlite3* db, Driver* driver);
Driver* driver_find_by_id(sqlite3* db, sqlite3_int64 id);
void driver_delete(sqlite3* db, Driver* driver);
void driver_update(sqlite3* db, Driver* driver);

unsigned int driver_count(sqlite3* db);

void driver_filtered(sqlite3* db, double maxKmFare, time_t minStage,void (*callback)(Driver*));
