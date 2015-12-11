#pragma once

#include <sqlite3.h>
#include "DBStructs.h"
#include "DBUtil.h"

#include <stdlib.h>

void init_statements(AppDB *db);
void release_statements(AppDB *db);

_id create_user(AppDB *db, const char *name, const char *password,
                const char *details);

_id create_post(AppDB *db, _id poster, _id answer_to, const char *text,
                const char *details);

_id like_post(AppDB *db, _id liker, _id liked_post);

_id send_message(AppDB *db, _id writer, _id receiver, const char *body,
                 const char *attachments);

/**
 * \param[out] messages Array to write messages
 * \param[in] max_messages Number of messages to fetch
 * \returns number of received messages
*/
size_t receive_messages(AppDB *db, _id receiver, const Message *messages,
                        size_t max_messages);

/**
 * \param[out] posts Array to write posts
 * \param[in] max_posts Number of posts to fetch
 * \returns number of fetched posts
*/
size_t read_users_posts(AppDB *db, _id poster, Post *posts, size_t max_posts);
