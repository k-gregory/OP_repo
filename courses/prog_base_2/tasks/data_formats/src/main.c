#include <stdlib.h>
#include <stdio.h>

#include <libxml/parser.h>

int main(void){
  LIBXML_TEST_VERSION;
  xmlCleanupParser();
  return EXIT_SUCCESS;
}
