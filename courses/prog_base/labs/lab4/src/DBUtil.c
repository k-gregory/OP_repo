#include "DBUtil.h"
#include "DBQueries.h"

#include <sqlite3.h>
#include <stdlib.h>
#include <stdio.h>

AppDB *init_db(const char *db_filename) {
  AppDB *db = malloc(sizeof(AppDB));

  if (sqlite3_open(db_filename, &db->db)) {
    fprintf(stderr, "Can't open db: %s\n", sqlite3_errmsg(db->db));
    sqlite3_close(db->db);
    return NULL;
  }
  init_statements(db);
  return db;
}

void close_db(AppDB *db) {
  release_statements(db);
  sqlite3_close(db->db);
  free(db);
}
