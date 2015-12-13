#include "DBUtil.h"
#include "DBQueries.h"
#include "Views.h"

#include <sqlite3.h>
#include <stdlib.h>
#include <stdio.h>

#define LEN(arr) (sizeof(arr)/sizeof((arr)[0]))

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

  _id a = create_user(db, "Larin", "Password", "Some details");
  _id b = create_user(db, "Pomidor", "test...", "Attached");

  post_wall(db,a,"Very good", NULL);
  post_wall(db,a,"Oh good", "Nice");
  PostV* p = new_post_v();
  read_user_wall(db,a,p,1);
  printf("Found post: \"%s\" by %s\n", p->body, p->author_name);
  delete_post_v(p);

  send_message(db, a, b, "Verni moi dengi", "Mghaz");

  InMessageV msgs[10];
  for(size_t i = 0; i< LEN(msgs);i++)
      init_in_message__v(&msgs[i]);

  for(int i =0; i<receive_messages(db, b, msgs, 10);i++){
      printf("%s wrote: \"%s\" and added: \"%s\"\n", msgs[i].sender_name, msgs[i].body,
              msgs[i].attachments);
  }

  for(size_t i = 0; i< LEN(msgs);i++)
      finalize_in_message_v(&msgs[i]);
  close_db(db);
  return EXIT_SUCCESS;
}
