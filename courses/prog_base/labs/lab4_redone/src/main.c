#include "DBUtil.h"

#include <sqlite3.h>
#include <stdlib.h>
#include <stdio.h>

int main(int argc, char* argv[]){
  sqlite3* db;
  if(argc!=2) {
    fprintf(stderr, "Usage: %s db_filename", argv[0]);
    return EXIT_FAILURE;
  }

  if((db = init_db(argv[1]))==NULL){
    return EXIT_FAILURE;
  }


  close_db(db);
  return EXIT_SUCCESS;
}
