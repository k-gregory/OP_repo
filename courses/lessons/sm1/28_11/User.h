#pragma oncea

#include <time.h>

#define NAME_LENGTH 20

typedef struct _User{
  char username[NAME_LENGTH];
  unsigned long long password_hash;
  time_t birth_date;
  time_t reg_date;
} User;

User* User_new(const char* name, const char* pass, time_t birth_date, time_t reg_date);
void User_delete(User* u);
unsigned long long hash_password(const char* str);
