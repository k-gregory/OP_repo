#include "DBUtil.h"
#include "DBQueries.h"

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

  _id a =  create_user(db,"Ogirok", "Password", "Some details");
  _id b =  create_user(db,"Pomidor","Oh sosi suka...","Attached");


  init_friendship(db,b,a);
  accept_friendship(db,a,b);

  close_db(db);
  return EXIT_SUCCESS;
}
