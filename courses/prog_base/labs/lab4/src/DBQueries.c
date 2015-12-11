#include "DBQueries.h"
#include "DBStructs.h"

#include <stdlib.h>
#include <string.h>

enum PreparedStatements {
  PL_FIRST = -1,
  CREATE_USER,
  CREATE_POST,
  LIKE_POST,
  WRITE_MESSAGE,
  RECEIVE_MESSAGES,
  READ_USERS_POSTS,
  PL_LAST
};

#define NSTATEMENTS (PL_LAST - PL_FIRST - 1)

void init_statements(AppDB *db) {
  sqlite3 *DB = db->db;
  db->statements = malloc(sizeof(sqlite3_stmt *) * NSTATEMENTS);
  sqlite3_stmt **STMT = db->statements;

  sqlite3_prepare_v2(
      DB, "insert into User(name, password, details) values (?,?,?);", -1,
      &STMT[CREATE_USER], NULL);

  sqlite3_prepare_v2(DB, "insert into Post("
                         "author_id, answer_to, likes, body, attachments) "
                         "values (?,?,0,?,?);",
                     -1, &STMT[CREATE_POST], NULL);

  sqlite3_prepare_v2(DB, "update Post set likes = likes+1 where id = ?;"
                         "insert into Like(liker_id, post_id) values (?,?);",
                     -1, &STMT[LIKE_POST], NULL);

  sqlite3_prepare_v2(
      DB, "insert into Message(sender_id, receiver_id, post_date , body, attachments) "
          "values (?, ?, datetime() , ?, ?);",
      -1, &STMT[WRITE_MESSAGE], NULL);

  sqlite3_prepare_v2(DB, "select (id,sender_id,body,attachments)"
                         " from Message where receiver_id = ? limit ?;",
                     -1, &STMT[RECEIVE_MESSAGES], NULL);

  sqlite3_prepare_v2(DB, "select * from Post where author_id = ? limit ?;", -1,
                     &STMT[READ_USERS_POSTS], NULL);
}
void release_statements(AppDB *db) {
  for (size_t i = 0; i < NSTATEMENTS; i++)
    sqlite3_finalize(db->statements[i]);
  free(db->statements);
}

_id create_user(AppDB *db, const char *name, const char *password,
                const char *details) {
  sqlite3_bind_text(db->statements[CREATE_USER], 1, name, -1, SQLITE_STATIC);
  sqlite3_bind_text(db->statements[CREATE_USER], 2, password, -1,
                    SQLITE_STATIC);
  sqlite3_bind_text(db->statements[CREATE_USER], 3, details, -1, SQLITE_STATIC);

  sqlite3_step(db->statements[CREATE_USER]);
  sqlite3_reset(db->statements[CREATE_USER]);

  return sqlite3_last_insert_rowid(db->db);
}

_id create_post(AppDB *db, _id poster, _id answer_to, const char *text,
                const char *details) {
  sqlite3_bind_int64(db->statements[CREATE_POST], 1, poster);
  sqlite3_bind_int64(db->statements[CREATE_POST], 2, answer_to);
  sqlite3_bind_text(db->statements[CREATE_POST], 3, text, -1, SQLITE_STATIC);
  sqlite3_bind_text(db->statements[CREATE_POST], 4, details, -1, SQLITE_STATIC);

  sqlite3_step(db->statements[CREATE_POST]);
  sqlite3_reset(db->statements[CREATE_POST]);

  return sqlite3_last_insert_rowid(db->db);
}

_id like_post(AppDB *db, _id liker, _id liked_post) {
  sqlite3_bind_int64(db->statements[LIKE_POST], 1, liked_post);
  sqlite3_bind_int64(db->statements[LIKE_POST], 2, liker);
  sqlite3_bind_int64(db->statements[LIKE_POST], 3, liked_post);

  sqlite3_step(db->statements[LIKE_POST]);
  sqlite3_reset(db->statements[LIKE_POST]);

  return sqlite3_last_insert_rowid(db->db);
}

_id send_message(AppDB *db, _id writer, _id receiver, const char *body,
                 const char *attachments) {
  sqlite3_bind_int64(db->statements[WRITE_MESSAGE], 1, writer);
  sqlite3_bind_int64(db->statements[WRITE_MESSAGE], 2, receiver);
  sqlite3_bind_text(db->statements[WRITE_MESSAGE], 3, body, -1, SQLITE_STATIC);
  sqlite3_bind_text(db->statements[WRITE_MESSAGE], 4, attachments, -1,
                    SQLITE_STATIC);


  printf("%d",sqlite3_step(db->statements[WRITE_MESSAGE]));
  sqlite3_reset(db->statements[WRITE_MESSAGE]);

  return sqlite3_last_insert_rowid(db->db);
}

size_t receive_messages(AppDB *db, _id receiver, Message *messages,
                        int max_messages) {
  size_t fetched = 0;

  sqlite3_bind_int64(db->statements[RECEIVE_MESSAGES], 1, receiver);
  sqlite3_bind_int(db->statements[RECEIVE_MESSAGES], 2, max_messages);

  while (sqlite3_step(db->statements[RECEIVE_MESSAGES]) == SQLITE_ROW) {
    Message msg;
    msg.id = sqlite3_column_int64(db->statements[RECEIVE_MESSAGES], 0);
    msg.receiver = receiver;
    msg.sender = sqlite3_column_int64(db->statements[RECEIVE_MESSAGES], 1);
    strcpy(msg.body, sqlite3_column_text(db->statements[RECEIVE_MESSAGES], 2));
    strcpy(msg.attachments,
           sqlite3_column_text(db->statements[RECEIVE_MESSAGES], 3));
    printf("%s\n", msg.body);
    messages[fetched++] = msg;
  }

  sqlite3_reset(db->statements[RECEIVE_MESSAGES]);
  return fetched;
}
