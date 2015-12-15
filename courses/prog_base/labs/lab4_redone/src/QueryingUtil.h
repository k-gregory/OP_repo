#pragma once

// Specified in ../sql/create_system_records.sql
#define WALL_POST 1

#define def_stmt(expr)                                                         \
  static sqlite3_stmt *q = NULL;                                               \
  if (q == NULL)                                                               \
    sqlite3_prepare_v2(db, expr, -1, &q, NULL);

#define col_int(index) sqlite3_column_int(q, index)
#define col_text(index) ((char *)sqlite3_column_text(q, index))
#define col_id(index) sqlite3_column_int64(q, index)
#define col_int64 col_id

#define bind_text(index, text)                                                 \
  sqlite3_bind_text(q, index, text, -1, SQLITE_STATIC)
#define bind_id(index, bound_id) sqlite3_bind_int64(q, index, bound_id)
#define bind_int(index, bound_int) sqlite3_bind_int(q, index, bound_int)

#define getindex(name) sqlite3_bind_parameter_index(q, name)

#define bind_text_v(name, text) bind_text(getindex(name), text)
#define bind_id_v(name, bound_id) bind_id(getindex(name), bound_id)
#define bind_int_v(name, bound_int) bind_int(getindex(name), bound_int)
