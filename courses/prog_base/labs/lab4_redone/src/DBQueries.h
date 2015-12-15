#pragma once

#include "types.h"

#include <sqlite3.h>

_id create_user(sqlite3 *db, const char *name, const char *password,
                const char *details);
void delete_user(sqlite3 *db, _id user);

_id create_post(sqlite3 *db, _id author, _id related_post, const char *body,
                const char *arrachments);
_id post_wall(sqlite3 *db, _id author, const char *body,
              const char *attachments);
void remove_post(sqlite3 *db, _id post);
void like_post(sqlite3 *db, _id liker, _id liked_post);

void init_friendship(sqlite3 *db, _id initiator, _id acceptor);
void decline_friendship(sqlite3 *db, _id acceptor, _id declined_friend);
void accept_friendship(sqlite3 *db, _id acceptor, _id accepted_friend);
void remove_friend(sqlite3 *db, _id remover, _id removed);

void send_message(sqlite3 *db, _id sender, _id receiver, const char *body,
                  const char *attachments);
