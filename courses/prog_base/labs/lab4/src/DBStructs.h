#pragma once

#include <sqlite3.h>

#define MAX_NAME_LENGTH 30
#define MAX_PASSWORD_LENGTH 10
#define MAX_USER_DETAILS_LENGTH 400
#define MAX_POST_LENGTH 300
#define MAX_MESSAGE_LENGTH 130
#define MAX_ATTACHMENTS_LENGTH 100

typedef sqlite3_int64 _id;

typedef struct _User {
  _id id;
  char name[MAX_NAME_LENGTH];
  char password[MAX_PASSWORD_LENGTH];
  char details[MAX_USER_DETAILS_LENGTH];
} User;

typedef struct _Post {
  _id id;
  _id author;
  _id answererd_post;
  int likes;
  char text[MAX_POST_LENGTH];
  char attachments[MAX_ATTACHMENTS_LENGTH];
} Post;

typedef struct _Like {
  _id id;
  _id liker;
  _id post;
} Like;

typedef struct _Message {
  _id id;
  _id sender;
  _id receiver;
  char body[MAX_MESSAGE_LENGTH];
  char attachments[MAX_ATTACHMENTS_LENGTH];
} Message;
