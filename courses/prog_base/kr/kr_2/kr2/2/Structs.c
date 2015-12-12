#include "Structs.h"

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

static const char *get_country(enum Country c) {
  switch (c) {
  case Ukraine:
    return "Ukraine";
    break;
  case NotUkraineYet:
    return "not Ukraine";
    break;
  default:
    return "unknown country";
  }
}

void print_writer(Writer *w) {
  printf("Writer %s born at %s in %s", w->name, ctime(&w->birth_date),
         get_country(w->homeland));
}

void print_book(Book *b) {
  printf("Book by %s published in %s by %s\n", b->title,
         ctime(&b->publication_time), b->author->name);
}

void writer_c_3(Writer *w, const char *name, time_t birth_date,
                enum Country homeland) {
  strcpy(w->name, name);
  w->birth_date = birth_date;
  w->homeland = homeland;
}

void book_c_4(Book *b, const char *title, const char *description,
              time_t publication_time, Writer *author) {
  strcpy(b->title, title);
  strcpy(b->description, description);
  b->publication_time = publication_time;
  b->author = author;
}

void writer_c(Writer *w) {
  writer_c_3(w, "Unknown author", time(NULL), Ukraine);
}

Writer *new_writer(void) { return malloc(sizeof(Writer)); }

void delete_writer(Writer *w) { free(w); }

int book_5_years_from_ukraine(Book *b) {
  time_t now = time(NULL);
  struct tm *ago = localtime(&now);
  ago->tm_year -= 5;
  if (b->author->homeland == Ukraine && b->publication_time > mktime(ago))
    return 1;
  return 0;
}

size_t filter_books(Book *res, Book *arr, size_t length, book_filter f) {
  size_t ret = 0;

  for (size_t i = 0; i < length; i++)
    if (f(&arr[i]))
      res[ret++] = arr[i];

  return ret;
}

size_t tasked_books(Book *res, Book *arr, size_t length) {
  return filter_books(res, arr, length, book_5_years_from_ukraine);
}

int cmp_writers(const Writer *a, const Writer *b) {
  return memcmp(a, b, sizeof(Writer));
}

int cmp_books(const Book *a, const Book *b) {
  return memcmp(a, b, sizeof(Book));
}
