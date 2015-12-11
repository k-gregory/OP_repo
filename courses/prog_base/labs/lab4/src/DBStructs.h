#pragma once

#include <sqlite3.h>

#define MAX_NAME_LENGTH 30
#define MAX_PASSWORD_LENGTH 10
#define MAX_USER_DETAILS_LENGTH 400
#define MAX_POST_LENGTH 300
#define MAX_MESSAGE_LENGTH 130
#define MAX_ATTACHMENTS_LENGTH 100

typedef struct _User {
  sqlite3_int64 id;
  char name[MAX_NAME_LENGTH];
  char password[MAX_PASSWORD_LENGTH];
  char details[MAX_USER_DETAILS_LENGTH];
} User;

typedef struct _Post {
  sqlite3_int64 id;
  sqlite3_int64 author_id;
  sqlite3_int64 answer_to_post_id;
  int likes;
  char text[MAX_POST_LENGTH];
  char attachments[MAX_ATTACHMENTS_LENGTH];
} Post;

typedef struct _Like {
  sqlite3_int64 id;
  sqlite3_int64 liker_id;
  sqlite3_int64 post_id;
} Like;

typedef struct _Message {
  sqlite3_int64 id;
  sqlite3_int64 sender_id;
  sqlite3_int64 receiver_id;
  char text[MAX_MESSAGE_LENGTH];
  char attachments[MAX_ATTACHMENTS_LENGTH];
} Message;
