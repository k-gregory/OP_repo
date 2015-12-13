#include "Views.h"

#include "QueryingUtil.h"

#include <stdlib.h>
#include <string.h>
#include <time.h>

//Specified in ../sql/create_system_records.sql

static void assign_text(char** dest, const char* src){
    if(src==NULL)
        *dest = NULL;
    else{
        *dest = malloc(strlen(src)+1);
        strcpy(*dest,src);
    }
}

void init_in_message__v(InMessageV *msg){
    msg->attachments = NULL;
    msg->body = NULL;
    msg->sender_name = NULL;
}

void finalize_in_message_v(InMessageV *msg){
    free(msg->attachments);
    free(msg->body);
    free(msg->sender_name);
}

InMessageV *new_in_message_v(void) {
  InMessageV *ret = malloc(sizeof(InMessageV));
  init_in_message__v(ret);
  return ret;
}

void ctr_in_message_v(InMessageV *msg, _id id, _id sender, time_t post_date,
                   char *body, char* attachments,
                   char* sender_name) {
    msg->id = id;
    msg->sender  =sender;
    msg->post_date = post_date;

   assign_text(&msg->body, body);
   assign_text(&msg->attachments, attachments);
   assign_text(&msg->sender_name, sender_name);
}

void delete_in_message_v(InMessageV *o) {
  finalize_in_message_v(o);
  free(o);
}

int receive_messages(sqlite3 *db, _id receiver, InMessageV *res, int limit) {
  int received = 0;
  def_stmt("select "
           "s.name, m.id, sender_id ,post_date,body, attachments "
           "from Message m "
           "left join User s on sender_id = s.id "
           "where receiver_id = @receiver "
           "order by -post_date limit @limit");

  bind_id_v("@receiver", receiver);
  bind_int_v("@limit", limit);

  while (sqlite3_step(q) == SQLITE_ROW)
      ctr_in_message_v(&res[received++],
                    col_id(1),
                    col_id(2),
                    col_int64(3),
                    col_text(4),
                    col_text(5),
                    col_text(0)
                    );

  sqlite3_reset(q);
  return received;
}

void init_post_v(PostV *post){
    post->attachments = NULL;
    post->body = NULL;
    post->author_name = NULL;
}

void finalize_post_v(PostV *post){
    free(post->attachments);
    free(post->body);
    free(post->author_name);
}

PostV* new_post_v(void){
    PostV* ret = malloc(sizeof(PostV));
    init_post_v(ret);
    return ret;
}

void ctr_post_v(PostV *post, _id id,_id related_post, _id author, time_t post_date, char *body, char *attachments, char *author_name){
    post->id = id;
    post->related_post = related_post;
    post->author = author;
    post->post_date = post_date;
    assign_text(&post->body,body);
    assign_text(&post->attachments, attachments);
    assign_text(&post->author_name, author_name);
}

void delete_post_v(PostV *post){
    finalize_post_v(post);
    free(post);
}

int read_responces(sqlite3 *db, _id post, PostV* res, int limit){
    int received = 0;
    def_stmt("select "
             "s.name, p.id, related_post,author_id, post_date, body, attachments "
             "from Post p "
             "left join User s on author_id = s.id "
             "where related_post = @post "
             "order by -post_date limit @limit");

    bind_id_v("@post", post);
    bind_id_v("@limit", limit);

    while(sqlite3_step(q)==SQLITE_ROW)
        ctr_post_v(&res[received++],
                col_id(1),
                col_id(2),
                col_id(3),
                col_int64(4),
                col_text(5),
                col_text(6),
                col_text(0));

    sqlite3_reset(q);
    return received;
}
int read_user_wall(sqlite3 *db, _id user, PostV *res, int limit){
    int received = 0;
    def_stmt("select "
             "s.name, p.id, related_post,author_id, post_date, body, attachments "
             "from Post p "
             "left join User s on author_id = s.id "
             "where related_post = @wall and author_id = @user "
             "order by -post_date limit @limit");

    bind_id_v("@wall", WALL_POST);
    bind_id_v("@user", user);
    bind_id_v("@limit", limit);

    while(sqlite3_step(q)==SQLITE_ROW){
        ctr_post_v(&res[received++],
                col_id(1),
                col_id(2),
                col_id(3),
                col_int64(4),
                col_text(5),
                col_text(6),
                col_text(0));
    }

    sqlite3_reset(q);
    return received;
}
