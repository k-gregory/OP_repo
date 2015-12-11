#pragma once

#include <sqlite3.h>
#include "DBStructs.h"
#include "DBUtil.h"

#include <stdlib.h>

User *create_user(AppDB *db, const char *name, const char *password,
                  const char *details);

Post *create_post(AppDB *db, const User *poster, const Post *answer_to,
                  const char *text, const char *attachments);

Like *like_post(AppDB *db, const User *liker, const Post *liked_post);

Message *write_message(AppDB *db, const User *writer, const User *receiver,
                       const char *text, const char *attachments);

/** \returns number of received messages */
size_t receive_messages(AppDB *db, const User *receiver, const Message *out,
                        size_t max_messages);

/** \returns number of received messages */
size_t read_users_posts(AppDB *db, const User *poster, const Post *posts,
                        size_t max_posts);
