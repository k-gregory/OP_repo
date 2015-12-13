#include "DBQueries.h"
#include "types.h"

#include <sqlite3.h>
#include <stdlib.h>

#define def_stmt(expr) static sqlite3_stmt* q = NULL ;\
  if(q==NULL) sqlite3_prepare_v2(db, expr, -1, &q, NULL);

#define col_int(index) sqlite3_column_int(q, index)
#define col_text(index) sqlite3_column_text(q, index)
#define col_id(index) sqlite3_column_int64(q, index)

#define bind_text(index, text) sqlite3_bind_text(q,index, text, -1, SQLITE_STATIC)
#define bind_id(index, bound_id) sqlite3_bind_int64(q, index, bound_id)
#define bind_int(index, bound_int) sqlite3_bind_int(q,index, bound_int)

#define getindex(name) sqlite3_bind_parameter_index(q, name)

#define bind_text_v(name, text) bind_text(getindex(name), text)
#define bind_id_v(name, bound_id) bind_id(getindex(name), bound_id)
#define bind_int_v(name, bound_int) bind_int(getindex(name), bound_int)

_id create_user(sqlite3* db,const char* name, const char* password, const char* details){
  def_stmt("insert into User(name, password, details) values(@name,@password,@details)");

  bind_text_v("@name",name);
  bind_text_v("@password",password);
  bind_text_v("@details", details);

  sqlite3_step(q);
  sqlite3_reset(q);
  return sqlite3_last_insert_rowid(db);
}

void delete_user(sqlite3 *db, _id user){
    def_stmt("delete from User where id = @user");

    bind_id_v("@user", user);

    sqlite3_step(q);
    sqlite3_reset(q);
}

_id create_post(sqlite3* db, _id author, _id answer_to, const char* body, const char* attachments){
  def_stmt("insert into Post(author_id, answer_to, body, post_date, attachments)"
           "values (@author_id, @answer_to, @body, strftime('%s','now'), @attachments)");

  bind_id_v("@author_id", author);
  bind_id_v("@answer_to", answer_to);
  bind_text_v("@body", body);
  bind_text_v("@attachments", attachments);

  sqlite3_step(q);

  sqlite3_reset(q);
  return sqlite3_last_insert_rowid(db);
}

void remove_post(sqlite3* db, _id post){
    def_stmt("delete from Post where id = @post");

    bind_id_v("@post", post);

    sqlite3_step(q);
    sqlite3_reset(q);
}

static int count_likes_by_user(sqlite3* db, _id liker, _id post){
    int res;
    def_stmt("select count(rowid) from Like "
             "where liker_id = @liker and post_id = @post");

    bind_id_v("@liker", liker);
    bind_id_v("@post", post);

    sqlite3_step(q);
    res = col_int(0);

    sqlite3_reset(q);
    return res;
}

static void do_like_post(sqlite3* db, _id liker, _id liked_post){
    def_stmt("insert into Like(liker_id, post_id) values (@liker, @liked_post)");

    bind_id_v("@liker", liker);
    bind_id_v("@liked_post", liked_post);

    sqlite3_step(q);
    sqlite3_reset(q);
}

static void do_dislike_post(sqlite3* db, _id liker, _id liked_post){
    def_stmt("delete from Like where liker_id = @liker and post_id = @liked_post");

    bind_id_v("@liker", liker);
    bind_id_v("@liked_post", liked_post);

    sqlite3_step(q);
    sqlite3_reset(q);
}

void like_post(sqlite3 *db, _id liker, _id liked_post){
    if(count_likes_by_user(db,liker,liked_post)>0)
        do_dislike_post(db,liker,liked_post);
    else do_like_post(db,liker,liked_post);
}



void init_friendship(sqlite3 *db, _id initiator, _id acceptor){
    def_stmt("insert into FriendInvite(inviter, invited) values(@a,@b)");

    bind_id_v("@a", initiator);
    bind_id_v("@b", acceptor);

    sqlite3_step(q);
    sqlite3_reset(q);
}

static int remove_invitation(sqlite3* db, _id inviter, _id invited){
    def_stmt("delete from FriendInvite "
             "where inviter = @inviter and invited = @invited");

    bind_id_v("@invited", invited);
    bind_id_v("@inviter", inviter);

    sqlite3_step(q);
    sqlite3_reset(q);
    return sqlite3_changes(db);
}

void decline_friendship(sqlite3 *db, _id acceptor, _id declined_friend){
    remove_invitation(db,acceptor, declined_friend);
}

static void register_friend(sqlite3* db, _id a, _id b){
    def_stmt("insert into Friends(user_a,user_b) values(@a,@b)");
    bind_id_v("@a", a);
    bind_id_v("@b", b);

    sqlite3_step(q);
    sqlite3_reset(q);
}

void accept_friendship(sqlite3 *db, _id acceptor, _id accepted_friend){
    if(remove_invitation(db,accepted_friend, acceptor)>0){
    remove_invitation(db,acceptor, accepted_friend);
    register_friend(db,acceptor, accepted_friend);
    register_friend(db,accepted_friend, acceptor);
    }
}

static void do_remove_friend(sqlite3 *db, _id remover, _id removed){
    def_stmt("remove from Friends where user_a = @remover and user_b = @removed");

    bind_id_v("@remover", remover);
    bind_id_v("@removed", removed);

    sqlite3_step(q);
    sqlite3_reset(q);
}

void remove_friend(sqlite3 *db, _id remover, _id removed){
    do_remove_friend(db,remover,removed);
    do_remove_friend(db,removed,remover);

    init_friendship(db,removed, remover);
}

void send_message(sqlite3 *db, _id sender, _id receiver, const char *body, const char *attachments){
    def_stmt("insert into Message(sender_id,receiver_id,post_date,body,attachments) "
             "values (@sender, @receiver, strftime('%s','now'), @body, @attachments)");

    bind_id_v("@sender", sender);
    bind_id_v("@receiver", receiver);
    bind_text_v("@body", body);
    bind_text_v("@attachments", attachments);

    sqlite3_step(q);
    sqlite3_reset(q);
}
