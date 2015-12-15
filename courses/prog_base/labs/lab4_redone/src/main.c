#include "DBUtil.h"
#include "DBQueries.h"
#include "Views.h"
#include "Loop.h"

#include <sqlite3.h>
#include <stdlib.h>
#include <stdio.h>

#define LEN(arr) (sizeof(arr) / sizeof((arr)[0]))

void configure_db(sqlite3 *db) {
  sqlite3_exec(db, "PRAGMA foreign_keys  = ON", NULL, NULL, NULL);
}

int main(int argc, char *argv[]) {
  sqlite3 *db;
  if (argc != 2) {
    fprintf(stderr, "Usage: %s db_filename", argv[0]);
    return EXIT_FAILURE;
  }

  if ((db = init_db(argv[1])) == NULL) {
    return EXIT_FAILURE;
  }

  configure_db(db);

  app_loop(db);

  close_db(db);
  return EXIT_SUCCESS;
}
