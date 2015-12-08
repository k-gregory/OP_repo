#include <sqlite3.h>

#include <stdlib.h>
#include <stdio.h>

int main(int argc, char* argv[]){
  int rc;
  sqlite3* db;
  if(argc!=2){
    fprintf(stderr, "Usage: %s dbname\n",argv[0]);
    return EXIT_FAILURE;
  }

  if(sqlite3_open(argv[1], &db)){
    fprintf(stderr, "Can't open db: %s\n", sqlite3_errmsg(db));
    sqlite3_close(db);
    return EXIT_FAILURE;
  }

  return EXIT_SUCCESS;
}
