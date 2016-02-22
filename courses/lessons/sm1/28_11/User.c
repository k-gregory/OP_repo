#include "User.h"

#include <time.h>
#include <stdlib.h>
#include <string.h>

unsigned long long hash_pass(const char* str){
  unsigned long long hash = 0;
  while(*str){
    hash = hash*101+*str++;
  }
  return hash;
}

User* User_new(const char* name, const char* pass, time_t birth_date, time_t reg_date){
  User* u = malloc(sizeof(User));
  strcpy(u->username, name);
  u->password_hash = hash_pass(pass);
  u->birth_date = birth_date;
  u->reg_date = reg_date;
  return u;
}
