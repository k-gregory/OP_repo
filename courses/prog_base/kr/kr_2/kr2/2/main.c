#include <stdlib.h>

#include "Structs.h"

#define LEN(arr) (sizeof(arr) / sizeof((arr)[0]))

int main(void) {
  Book books[20];
  Book filtBooks[20];
  Writer w[2];
  writer_c_3(w, "ogo", 2015, Ukraine);
  writer_c_3(w + 1, "gogo", 2016, NotUkraineYet);

  for (size_t i = 0; i < LEN(books); i++)
    book_c_4(&books[i], "Test book", "Test descr", time(NULL), &w[rand() % 2]);

  for (size_t i = 0; i < tasked_books(filtBooks, books, LEN(books)); i++) {
    print_book(&books[i]);
  }

  printf("%d\n", cmp_writers(w, w + 1));

  print_writer(w);
  return EXIT_SUCCESS;
}
