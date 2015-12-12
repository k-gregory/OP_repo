#pragma once

#include "types.h"

#include <sqlite3.h>

_id create_user(sqlite3* db,const char* filename, const char* password, const char* details);
