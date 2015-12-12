#include "Structs.h"

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

static const char* get_country(enum Country c){
  switch(c){
    case Ukraine: return "Ukraine";break;
    case NotUkraineYet: return "not Ukraine"; break;
    default: return "unknown country";
  }
}

void print_writer(Writer* w){
  printf("Writer %s born at %s in %s",
      w->name, ctime(&w->birth_date), get_country(w->homeland));
}

void writer_c_3(Writer* w, const char* name, time_t birth_date, enum Country homeland){
  strcpy(w->name,name);
  w->birth_date = birth_date;
  w->homeland = homeland;
}

void writer_c(Writer* w){
  writer_c_3(w, "Unknown author", time(NULL), Ukraine);
}

Writer* new_writer(void){
  return malloc(sizeof(Writer));
}

void delete_writer(Writer* w){
  free(w);
}

int book_5_years_from_ukraine(Book* b){
  time_t now = time(NULL);
  struct tm* ago = localtime(&now);
  ago->tm_year-=5;
  if(b->author->homeland == Ukraine && b->publication_time > mktime(ago))
    return 1;
  return 0;
}

size_t filter_books(Book* res, const Book* arr, size_t length, book_filter f){
}
