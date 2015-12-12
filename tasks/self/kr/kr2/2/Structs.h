#pragma once

#include <stdlib.h>
#include <time.h>

#define WRITER_NAME_LENGTH 20
#define BOOK_NAME_LENGTH 20
#define BOOK_DESCRIPTION_LENGTH 100

enum Country{
  Ukraine, NotUkraineYet
};

typedef struct _Writer {
  char name[WRITER_NAME_LENGTH];
  time_t birth_date;
  enum Country homeland;
} Writer;

void print_writer(Writer* w);

Writer* new_writer(void);
void delete_writer(Writer* w);

void writer_c(Writer* w);
void writer_c_3(Writer* w, const char* name, time_t birth_date,enum Country homeland);

typedef struct _Book {
  char title[BOOK_NAME_LENGTH];
  char description[BOOK_DESCRIPTION_LENGTH];
  time_t publication_time;
  Writer* author;
} Book;

typedef int (*book_filter)(Book* book);
typedef int (*writer_filter)(Writer* writer);

void print_book(Book* book);

Book* new_book(void);
void  delete_book(void);

void book_c(Book* b);
void book_c_4(Book* b);

size_t filter_books(Book* res,const Book* arr, size_t length, book_filter f);

size_t tasked_books(Book* res, Book* arr, size_t length);
