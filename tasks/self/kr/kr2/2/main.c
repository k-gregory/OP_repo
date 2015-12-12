#include <stdlib.h>

#include "Structs.h"

int main(void){
  Writer* w = new_writer();
  writer_c_3(w,"Ogo",  1488, Ukraine);
  print_writer(w);
  return EXIT_SUCCESS;
}
