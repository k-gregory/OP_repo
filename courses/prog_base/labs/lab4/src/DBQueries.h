#pragma once

#include <sqlite3.h>
#include "DBStructs.h"
#include "DBUtil.h"

#include <stdlib.h>

void init_statements(AppDB *db);
void release_statements(AppDB *db);

sqlite3_int64 create_user(AppDB *db, const char *name, const char *password,
                          const char *details);

sqlite3_int64 create_post(AppDB *db, sqlite3_int64 poster, sqlite3_int64 answer_to,
                          const char *text, const char *details);

sqlite3_int64 like_post(AppDB *db, sqlite3_int64 liker, sqlite3_int64 liked_post);

Message write_message(AppDB *db, sqlite3_int64 writer, sqlite3_int64 receiver,
                      const char *text, const char *attachments);

/**
 * \param[out] messages Array to write messages
 * \param[in] max_messages Number of messages to fetch
 * \returns number of received messages
*/
size_t receive_messages(AppDB *db, sqlite3_int64 receiver,
                        const Message *messages, size_t max_messages);

/**
 * \param[out] posts Array to write posts
 * \param[in] max_posts Number of posts to fetch
 * \returns number of fetched posts
*/
size_t read_users_posts(AppDB *db, sqlite3_int64 poster, Post *posts,
                        size_t max_posts);
