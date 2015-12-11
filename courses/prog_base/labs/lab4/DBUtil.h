#pragma once

#include <sqlite3.h>

typedef struct {
  sqlite3 *db;
  sqlite3_stmt *statements;
} AppDB;

AppDB* init_db(const char* db_filename);
void close_db(AppDB* db);
