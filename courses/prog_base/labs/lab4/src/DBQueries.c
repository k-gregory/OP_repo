#include "DBQueries.h"

#include <stdlib.h>

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
      DB, "insert into Message(sender_id, receiver_id, body, attachments) "
          "values (?, ?, ?, ?);",
      -1, &STMT[WRITE_MESSAGE], NULL);

  sqlite3_prepare_v2(DB,
                     "select * from Message where receiver_id = ? limit ? ;",
                     -1, &STMT[RECEIVE_MESSAGES], NULL);

  sqlite3_prepare_v2(DB, "select * from Message where author_id = ? limit ? ;",
                     -1, &STMT[READ_USERS_POSTS], NULL);
}
void release_statements(AppDB *db) {
  for (size_t i = 0; i < NSTATEMENTS; i++)
    sqlite3_finalize(db->statements[i]);
  free(db->statements);
}

sqlite3_int64 create_user(AppDB *db, const char *name, const char *password,
                          const char *details) {
  sqlite3_bind_text(db->statements[CREATE_USER], 1, name, -1, SQLITE_STATIC);
  sqlite3_bind_text(db->statements[CREATE_USER], 2, password, -1,
                    SQLITE_STATIC);
  sqlite3_bind_text(db->statements[CREATE_USER], 3, details, -1, SQLITE_STATIC);

  sqlite3_step(db->statements[CREATE_USER]);

  return sqlite3_last_insert_rowid(db->db);
}

sqlite3_int64 create_post(AppDB *db, sqlite3_int64 poster, sqlite3_int64 answer_to,
                          const char *text, const char *details) {
    sqlite3_bind_int64(db->statements[CREATE_POST], 1, poster);
    sqlite3_bind_int64(db->statements[CREATE_POST], 2, answer_to);
    sqlite3_bind_text(db->statements[CREATE_POST],3, text,-1, SQLITE_STATIC);
    sqlite3_bind_text(db->statements[CREATE_POST], 4, details,-1, SQLITE_STATIC);

    sqlite3_step(db->statements[CREATE_POST]);

    return sqlite3_last_insert_rowid(db->db);
}
