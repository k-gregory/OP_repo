#pragma once 

#include <sqlite3.h>

sqlite3* init_db(const char* filename);
void close_db(sqlite3* db);
