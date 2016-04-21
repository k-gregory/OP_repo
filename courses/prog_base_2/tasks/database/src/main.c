#include "Driver.h"

#include <sqlite3.h>

#include <stdlib.h>
#include <stdio.h>
#include <time.h>

void configure_db(sqlite3 *db) {
  sqlite3_exec(db, "PRAGMA foreign_keys  = ON", NULL, NULL, NULL);
}


void test_cb(Driver* d){
    printf("Good driver:#%llu %s %s\n",d->id,d->name,d->surname);
}

int main(int argc, char *argv[]) {
  Driver* driver;
  sqlite3 *db;
  if (argc != 2) {
    fprintf(stderr, "Usage: %s db_filename", argv[0]);
    return EXIT_FAILURE;
  }

  if ((db = init_db(argv[1])) == NULL) {
    return EXIT_FAILURE;
  }

  configure_db(db);

  driver = driver_find_by_id(db,1);
  driver->car_average_speed = -400;
  driver_update(db,driver);
  driver_filtered(db,35,0,test_cb);
  printf("%p %s\n",driver,driver->car_manufacturer);
  printf("%u",driver_count(db));

  close_db(db);
  return EXIT_SUCCESS;
}
