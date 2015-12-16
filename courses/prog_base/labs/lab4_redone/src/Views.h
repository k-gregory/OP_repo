#pragma once

#include "DBQueries.h"
#include "types.h"

#include <sqlite3.h>
#include <stdlib.h>
#include <time.h>

typedef struct _UserV {
  _id id;
  char *name;
  char *password;
  char *details;
} UserV;

UserV *new_user_v(void);
void init_user_v(UserV *u);
void finalize_user_v(UserV *u);
void ctr_user_v(UserV *u, _id id, char *name, char *password, char *details);
void delete_user_v(UserV *u);

typedef struct _InMessageV {
  _id id;
  _id sender;
  time_t post_date;
  char *body;
  char *attachments;

  char *sender_name;
} InMessageV;

InMessageV *new_in_message_v(void);
void init_in_message_v(InMessageV *msg);
void finalize_in_message_v(InMessageV *msg);
void ctr_in_message_v(InMessageV *msg, _id id, _id sender, time_t post_date,
                      char *body, char *attachments, char *sender_name);
void delete_in_message_v(InMessageV *o);

typedef struct _PostV {
  _id id;
  _id related_post;
  _id author;
  time_t post_date;
  char *body;
  char *attachments;

  char *author_name;
} PostV;

PostV *new_post_v(void);
void init_post_v(PostV *post);
void finalize_post_v(PostV *post);
void ctr_post_v(PostV *post, _id id, _id related_post, _id author,
                time_t post_date, char *body, char *attachments,
                char *author_name);
void delete_post_v(PostV *post);

/**
 * \returns 0 if user doesn't exist
 */
int find_post_by_id(sqlite3 *db, _id id, PostV *res);

/**
 * \param[out] res Array to write received messages
 * \param[in] limit Max number of posts to receive
 * \returns number of received messages
 */
int receive_messages(sqlite3 *db, _id receiver, InMessageV *res, int limit);

/**
 * Read user's own posts(not responces)
 * \param[out] res Array to write recieved posts
 * \param[in] limit Max number of posts to receive
 * \returns number of received messages
 */
int read_user_wall(sqlite3 *db, _id user, PostV *res, int limit);
/**
 * \param[in] post related post
 * \param[out] res Array to write recieved posts
 * \param[in] limit Max number of posts to receive
 * \returns number of received messages
 */
int read_responces(sqlite3 *db, _id post, PostV *res, int limit);

/** Find user by name
 * \param[out] res Array to write found users
 * \param[in] limit Max number of users to find
 * \returns number of found users
 */

/**
 * \returns 0 if user doesn't exist
 */
int find_user_by_id(sqlite3 *db, _id id, UserV *res);

int find_users(sqlite3 *db, char *name, UserV *res, int limit);
/**
 * \param[in] user User which has friends
 * \param[out] res Array to write found friends
 * \param[in] limit Max number of friends to receive
 * \returns number of found users
 */
int list_friends(sqlite3 *db, _id user, UserV *res, int limit);
