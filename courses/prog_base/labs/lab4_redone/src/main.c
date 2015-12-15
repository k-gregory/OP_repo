#include "DBUtil.h"
#include "DBQueries.h"
#include "Views.h"
#include "Loop.h"

#include <sqlite3.h>
#include <stdlib.h>
#include <stdio.h>

#define fix_fgets(str) str[strcspn(str,"\r\n")] = '\0';
#define get_input fgets(param_buff, LEN(param_buff), stdin);\
                  fix_fgets(param_buff);

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

  //app_loop(db);
  UserV a[1];
  init_user_v(&a[0]);
  //printf("%d\n",find_users(db,"admin", a, 1));
  int x = find_users(db,"admin", a, 1);
  //finalize_user_v(&a[0]);
  //init_user_v(&a[0]);
  for(int i =0;i<x;i++)
      //FIXME:!!!!!! FIND USERS IS CALLED EVERY TIME!!!!!
  //for(int i =0;i<find_users(db,"admin", a, 1);i++){
      printf("ID:#%lld %s\n", a[i].id, a[i].name);
  //}
  finalize_user_v(&a[0]);

  UserV found[1];
  for(size_t i = 0; i< 1;i++)
      init_user_v(&found[i]);
  for(int i =0; i<find_users(db, "admin", found, 1); i++){
     // printf("ID:#%lld %s\n", found[i].id, found[i].name);
  }
  for(size_t i=0;i<1;i++)
      finalize_user_v(&found[i]);


  close_db(db);
  return EXIT_SUCCESS;
}
