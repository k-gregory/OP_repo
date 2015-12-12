#include "DBUtil.h"
#include "DBQueries.h"
#include "DBStructs.h"

#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#define LEN(arr) (sizeof(arr) / sizeof((arr)[0]))

_id register_new_user(AppDB *db) {
  char name_buff[MAX_NAME_LENGTH];
  char pass_buff[MAX_PASSWORD_LENGTH];
  puts("Enter new user name");
  fgets(name_buff, LEN(name_buff), stdin);
  puts("Enter new user password");
  fgets(pass_buff, LEN(pass_buff), stdin);
  name_buff[strcspn(name_buff, "\r\n")] = 0;
  pass_buff[strcspn(pass_buff, "\r\n")] = 0;
  return create_user(db, name_buff, pass_buff, NULL);
}

int main(int argc, char *argv[]) {
  char cli_buff[1024];
  AppDB *db;
  _id user;

  if (argc != 2) {
    fprintf(stderr, "Usage: %s dbname\n", argv[0]);
    return EXIT_FAILURE;
  }

  if (!(db = init_db(argv[1])))
    return EXIT_FAILURE;

  printf("Press enter to register new user or print your username\n");
  fgets(cli_buff, LEN(cli_buff), stdin);
  if (cli_buff[0] == '\n')
    user = register_new_user(db);
  else {
    cli_buff[strcspn(cli_buff, "\r\n")] = 0;
    _id users[10];
    size_t i = find_users_by_name(users, db, cli_buff);
    if (i == 0) {
      puts("Such user does not exists");
      return EXIT_FAILURE;
    } else if (i == 1) {
      user = users[0];
    } else {
      puts("There are more than one user with such name. Print ur uniq id");
      fgets(cli_buff, LEN(cli_buff), stdin);
      if (sscanf(cli_buff, "%lld", &user) != 1) {
        puts("You had to enter your id");
        return EXIT_FAILURE;
      }
    }
    User *u = malloc(sizeof(User));
    u = find_user_by_id(u, db, user);
    if (u == NULL) {
      puts("Such user does not exists");
      free(u);
      return EXIT_FAILURE;
    }
    char pass_buff[MAX_PASSWORD_LENGTH];
    puts("Enter password");
    fgets(pass_buff, LEN(pass_buff), stdin);
    pass_buff[strcspn(pass_buff, "\r\n")] = 0;
    if (strcmp(pass_buff, u->password) != 0) {
      puts("Wrong password!");
      return EXIT_FAILURE;
    }
    free(u);
  }

  puts("Print \"help\" for list of commands");
  for (;;) {
    char paramBuff[20];
    fgets(cli_buff, LEN(cli_buff), stdin);
    cli_buff[strcspn(cli_buff, "\r\n")] = 0;
    if (strcmp("help", cli_buff) == 0) {
      puts("Available commands: "
           "add_friend, list_friends, remove_friend, "
           "read_messages, write_message, "
           "read_posts, write_post, like_post");
      continue;
    }
    if (strcmp("read_messages", cli_buff) == 0) {
      printf("Enter amount of messages: ");
      fgets(paramBuff, LEN(paramBuff), stdin);
      int nmesg;
      if (sscanf(paramBuff, "%d", &nmesg) != 1)
        puts("You must enter nice number of messages to read");
      else {
        Message *msg = malloc(sizeof(Message) * nmesg);
        for (size_t i = 0; i < receive_messages(db, user, msg, nmesg); i++) {
          if (msg[i].sender != user)
            printf("========Message from %lld===========\n", msg[i].sender);
          else
            printf("===========Message to %lld ========\n", msg[i].receiver);
          puts(msg[i].body);
          puts("===========================");
        }
        puts("That's all...");
        free(msg);
      }
      continue;
    }
    if (strcmp("write_message", cli_buff) == 0) {
      printf("Enter receiver id: ");
      fgets(paramBuff, LEN(paramBuff), stdin);
      _id recv;
      if (sscanf(paramBuff, "%lld", &recv) != 1)
        puts("You had to write receiver id");
      else {
        char msg_buff[MAX_MESSAGE_LENGTH];
        puts("Now type your message");
        fgets(msg_buff, LEN(msg_buff), stdin);
        send_message(db, user, recv, msg_buff, NULL);
      }
    }
    if (strcmp("read_posts", cli_buff) == 0) {
        _id poster;
        printf("Enter poster id: ");
        fgets(paramBuff, LEN(paramBuff),stdin);
        if(sscanf(paramBuff,"%lld",&poster)!=1){
            puts("you shall put valid poster id");
            continue;
        }
        printf("Enter amount of posts: ");
        fgets(paramBuff, LEN(paramBuff), stdin);
        int nposts;
        if (sscanf(paramBuff, "%d", &nposts) != 1)
          puts("You must enter nice number of posts to read");
        else {
          Post *posts = malloc(sizeof(Post) * nposts);
          for (size_t i = 0; i < read_users_posts(db, poster, posts, nposts); i++)
              printf("#%lld by user %lld(%d likes) in responce to #%lld");
          puts("That's all...");
          free(posts);
        }
        continue;
    }
    if (strcmp("help", cli_buff) == 0) {
    }
    if (strcmp("help", cli_buff) == 0) {
    }
    if (strcmp("help", cli_buff) == 0) {
    }
  }

  close_db(db);
  return EXIT_SUCCESS;
}
