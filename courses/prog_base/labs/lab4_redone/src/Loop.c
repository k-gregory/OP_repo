#include "Loop.h"
#include "sqlite3.h"
#include "DBQueries.h"
#include "Views.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define LEN(arr) (sizeof(arr) / sizeof((arr)[0]))
#define CASE(input) if (strcmp(cli_buff, input) == 0)

UserV *logged_user = NULL;
UserV *selected_user = NULL;

void app_loop(sqlite3 *db) {
  char cli_buff[128];
  for (;;) {
    fgets(cli_buff, LEN(cli_buff), stdin);
    cli_buff[strcspn(cli_buff, "\n\r")] = 0;
    printf("\n%s\n", cli_buff);
    CASE("quit") break;
    CASE("login") {
      char in_buff[20];
      puts("Enter your id");
      fgets(in_buff, LEN(in_buff), stdin);
      puts("Enter your password");
    }
  }
}
