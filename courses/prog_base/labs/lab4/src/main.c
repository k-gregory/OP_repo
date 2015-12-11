#include "DBUtil.h"
#include "DBQueries.h"

#include <stdlib.h>
#include <stdio.h>

int main(int argc, char *argv[]) {
  AppDB *db;
  if (argc != 2) {
    fprintf(stderr, "Usage: %s dbname\n", argv[0]);
    return EXIT_FAILURE;
  }

  if (!(db = init_db(argv[1])))
    return EXIT_FAILURE;

  _id sender = create_user(db, "UserA", "pass", NULL);
  _id recv = create_user(db, "UserB", "pass2", NULL);

  send_message(db, sender, recv, "Privet", NULL);
  send_message(db, recv, sender, "Poka", NULL);

  Message msgs[100];
 // receive_messages(db,sender,msgs, 5);

  close_db(db);

  return EXIT_SUCCESS;
}
