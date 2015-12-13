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

/*
 * \param[out] res Array to write received messages
 * \parram[in] limit Max number of received messages
 */
int receive_messages(sqlite3 *db, _id receiver, InMessageV *res, int limit);
