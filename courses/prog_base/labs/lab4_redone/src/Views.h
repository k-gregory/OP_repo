#pragma once

#include "DBQueries.h"
#include "types.h"

#include <sqlite3.h>
#include <stdlib.h>
#include <time.h>

typedef struct _InMessageV {
  _id id;
  _id sender;
  time_t post_date;
  char *body;
  char *attachments;

  char *sender_name;
} InMessageV;


InMessageV *new_in_message_v(void);
void init_in_message__v(InMessageV* msg);
void finalize_in_message_v(InMessageV* msg);
void ctr_in_message_v(InMessageV *msg, _id id, _id sender, time_t post_date,
                    char *body,  char* attachments,
                    char* sender_name);
void delete_in_message_v(InMessageV *o);

typedef struct _PostV{
    _id id;
    _id related_post;
    _id author;
    int likes;
    time_t post_date;
    char *body;
    char *attachments;

    char* author_name;
} PostV;

PostV *new_post_v(void);
void init_post_v(PostV* post);
void finalize_post_v(PostV* post);
void ctr_post_v(PostV* post, _id id,_id related_post, _id author, time_t post_date, char* body, char* attachments, char *author_name);
void delete_post_v(PostV* post);

/*
 * \param[out] res Array to write received messages
 * \parram[in] limit Max number of posts to receive
 * \returns number of received messages
 */
int receive_messages(sqlite3 *db, _id receiver, InMessageV *res, int limit);

/*
 * Read user's own posts(not responces)
 * \param[out] res Array to write recieved posts
 * \parram[in] limit Max number of posts to receive
 * \returns number of received messages
 */
int read_user_wall(sqlite3* db, _id user, PostV* res, int limit);
/*
 * \param[in] post related post
 * \param[out] res Array to write recieved posts
 * \parram[in] limit Max number of posts to receive
 * \returns number of received messages
 */
int read_responces(sqlite3* db, _id post, PostV* res, int limit);

