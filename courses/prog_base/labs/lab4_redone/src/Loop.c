#include "Loop.h"
#include "sqlite3.h"
#include "DBQueries.h"
#include "Views.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define LEN(arr) (sizeof(arr) / sizeof((arr)[0]))
#define CASE(input) if (strcmp(cli_buff, input) == 0)

#define fix_fgets(str) str[strcspn(str,"\r\n")] = '\0';
#define get_input fgets(param_buff, LEN(param_buff), stdin);\
                  fix_fgets(param_buff);

UserV *logged_user = NULL;
UserV *selected_user = NULL;

void app_loop(sqlite3 *db) {
  char cli_buff[128];
  char param_buff[30];
  for (;;) {
    fgets(cli_buff, LEN(cli_buff), stdin);
    fix_fgets(cli_buff);

    CASE("quit") break;
    CASE("find_users"){
        UserV found[10];
        for(size_t i = 0; i< 10;i++)
            init_user_v(&found[i]);

        puts("Enter user name");
        get_input;
        fix_fgets(param_buff);

        //FIXME: FIND_USERS CALLED EVERY TIME!!!
        for(int i =0; i<find_users(db, param_buff, found, 10); i++){
            printf("ID:#%lld %s\n", found[i].id, found[i].name);
        }
        for(size_t i=0;i<10;i++)
            finalize_user_v(&found[i]);
    }
  }
}
