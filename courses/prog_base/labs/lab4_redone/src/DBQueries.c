#include "DBQueries.h"
#include "types.h"

#include <sqlite3.h>
#include <stdlib.h>

#define def_stmt(expr) static sqlite3_stmt* q = NULL ;\
  if(q==NULL) sqlite3_prepare_v2(db, expr, -1, &q, NULL);

#define bind_text(index, text) sqlite3_bind_text(q,index, text, -1, SQLITE_STATIC);
#define bind_id(index, bound_id) sqlite3_bind_int64(q, index, bound_id);

_id create_user(sqlite3* db,const char* name, const char* password, const char* details){
  def_stmt("insert into User(name, password, details) values(?,?,?)");

  bind_text(1,name);
  bind_text(2,password);
  bind_text(3, details);

  sqlite3_step(q);

  sqlite3_reset(q);
  return sqlite3_last_insert_rowid(db);
}

_id create_post(sqlite3* db, _id author, _id answer_to, const char* body, const char* attachments){
  def_stmt("insert into Post(author, answer_to, body, likes, post_date, attachments)
      values (?, ?, ?, 0)");
}
