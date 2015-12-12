#pragma once

#include "types.h"

#include <sqlite3.h>

_id create_user(sqlite3* db,const char* name, const char* password, const char* details);
_id create_post(sqlite3* db, _id author, _id answer_to, const char* body, const char* arrachments);
void like_post(sqlite3* db, _id liker, _id liked_post);
void init_friendship(sqlite3* db, _id initiator, _id acceptor);
void decline_friendship(sqlite3* db, _id acceptor, _id declined_friend);
void accept_friendship(sqlite3* db, _id acceptor, _id accepted_friend);
