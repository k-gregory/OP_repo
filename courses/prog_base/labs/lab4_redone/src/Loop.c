#include "Loop.h"
#include "sqlite3.h"
#include "DBQueries.h"
#include "QueryingUtil.h"
#include "Views.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX_USERS_FOUND 10
#define MAX_POSTS_READ 100

#define MAX_MSG_LENGTH 200

#define LEN(arr) (sizeof(arr) / sizeof((arr)[0]))
#define CASE(input) if (strcmp(cli_buff, input) == 0)

#define fix_fgets(str) str[strcspn(str, "\r\n")] = '\0';
#define get_input                                                              \
  fgets(param_buff, LEN(param_buff), stdin);                                   \
  fix_fgets(param_buff);

#define mgets(buff)                                                            \
  fgets(buff, LEN(buff), stdin);                                               \
  buff[strcspn(buff, "\r\n")] = '\0';
#define ensure_user_selected                                                   \
  if (selected_user == NULL) {                                                 \
    puts("First, select user by \"select_user\"");                             \
    return;                                                                    \
  }
#define ensure_post_selected                                                   \
  if (selected_post == NULL) {                                                 \
    puts("First, select post by \"select_post\"");                             \
    return;                                                                    \
  }
#define ensure_authentification                                                \
  if (logged_user == NULL) {                                                   \
    puts("Firstly, you have to login");                                        \
    return;                                                                    \
  }

#define post_body(post) (post.body != NULL ? post.body : "<empty post>\n")

sqlite3 *db;
UserV *logged_user;
UserV *selected_user;
PostV *selected_post;

static void _find_users(char *name) {
  UserV found[MAX_USERS_FOUND];
  for (size_t i = 0; i < LEN(found); i++)
    init_user_v(&found[i]);
  int n = find_users(db, name, found, MAX_USERS_FOUND);
  for (int i = 0; i < n; i++)
    printf("ID:#%lld %s\n", found[i].id, found[i].name);
  for (size_t i = 0; i < 10; i++)
    finalize_user_v(&found[i]);
}

static void _select_user(char *id) {
  _id s_id;
  if (sscanf(id, "%lld", &s_id) != 1) {
    puts("Failed to parse user id!");
    return;
  }
  if (s_id == ADMIN_ID) {
    puts("You can't login as admin, lold");
    return;
  }
  UserV *new_user = new_user_v();
  if (find_user_by_id(db, s_id, new_user) == 0) {
    puts("User with specified id not found! Try using \"find_users\"");
    delete_user_v(new_user);
    return;
  }
  delete_user_v(selected_user);
  selected_user = new_user;
  printf("Successfully selected user \"%s\"\n", selected_user->name);
}

static void _select_post(char *id) {
  _id p_id;
  if (sscanf(id, "%lld", &p_id) != 1) {
    puts("Failed to parse post id!");
    return;
  }

  if (p_id == WALL_POST) {
    puts("You can't select this post");
    return;
  }

  PostV *new_post = new_post_v();
  if (find_post_by_id(db, p_id, new_post) == 0) {
    puts("Post with specified id not found!");
    delete_post_v(new_post);
    return;
  }
  delete_post_v(selected_post);
  selected_post = new_post;
  printf("Selected post #%lld\n", selected_post->id);
}

static void _log_in(char *password) {
  ensure_user_selected;
  if (strcmp(password, selected_user->password) != 0) {
    puts("Invalid password!");
    return;
  }
  logged_user = selected_user;
  printf("Logged in as %s\n", logged_user->name);
}

static void _read_wall() {
  ensure_user_selected;
  PostV posts[MAX_POSTS_READ];
  for (size_t i = 0; i < LEN(posts); i++)
    init_post_v(&posts[i]);

  int n = read_user_wall(db, selected_user->id, posts, LEN(posts));
  printf("%d\n", n);
  for (int i = 0; i < n; i++)
    printf("ID:#%lld at %s(%d likes)\n%s", posts[i].id,
           ctime(&posts[i].post_date), count_likes(db, posts[i].id),
           posts[i].body != NULL ? posts[i].body : "<Empy post>\n");

  for (size_t i = 0; i < LEN(posts); i++)
    finalize_post_v(&posts[i]);
}

static void _read_responces() {
  ensure_post_selected;
  PostV posts[MAX_POSTS_READ];
  for (size_t i = 0; i < LEN(posts); i++)
    init_post_v(&posts[i]);

  int n = read_responces(db, selected_post->id, posts, LEN(posts));
  for (int i = 0; i < n; i++)
    printf("ID:#%lld by %s(%d likes) at %s%s\n", posts[i].id,
           posts[i].author_name, count_likes(db, posts[i].id),
           ctime(&posts[i].post_date), post_body(posts[i]));

  for (size_t i = 0; i < LEN(posts); i++)
    finalize_post_v(&posts[i]);
}

static void _make_responce() {
  char msg_buff[MAX_MSG_LENGTH];

  ensure_post_selected;
  ensure_authentification;

  puts("Enter your message");
  mgets(msg_buff);

  create_post(db, logged_user->id, selected_post->id, msg_buff, NULL);
}

void app_loop(sqlite3 *app_db) {
  selected_user = NULL;
  logged_user = NULL;
  selected_post = NULL;

  db = app_db;
  char cli_buff[128];
  char param_buff[30];
  for (;;) {
    puts("Enter command. \"help\" for list");
    mgets(cli_buff);

    CASE("quit") break;
    CASE("find_users") {
      puts("Enter user name");
      mgets(param_buff);
      puts("Found:");
      _find_users(param_buff);
    }
    CASE("select_user") {
      puts("Enter user id");
      mgets(param_buff);
      _select_user(param_buff);
    }
    CASE("select_post") {
      puts("Enter post id");
      mgets(param_buff);
      _select_post(param_buff);
    }

    CASE("login") {
      ensure_user_selected;
      puts("Enter user password");
      mgets(param_buff);
      _log_in(param_buff);
    }
    CASE("read_wall") _read_wall();
    CASE("responces") _read_responces();
    CASE("respond") _make_responce();
  }
}
