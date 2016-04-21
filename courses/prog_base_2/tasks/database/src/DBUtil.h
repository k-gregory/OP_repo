#pragma once

#include <sqlite3.h>

sqlite3 *init_db(char *filename);
void close_db(sqlite3 *db);
