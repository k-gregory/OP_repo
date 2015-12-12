#include "DBUtil.h"

#include <stdio.h>

sqlite3* init_db(const char* filename){
  sqlite3* db;
  if(sqlite3_open(filename,&db)){
    fprintf(stderr, "Can't open database: %s", sqlite3_errmsg(db));
    sqlite3_close(db);
    return NULL;
  };
 return db; 
}

void close_db(sqlite3* db){
  sqlite3_close(db);
}
