#include "Driver.h"
#include <libxml/parser.h>

#include <stdlib.h>
#include <stdio.h>

int main(int argc, char* argv[]){
  unsigned long n_drivers;
  LIBXML_TEST_VERSION;

  if(argc!=2){
    fputs("Specify xml file with drivers list", stderr);
    exit(EXIT_FAILURE);
  }

  Driver* drivers;
  n_drivers = drivers_parse_from_xml_file(&drivers, argv[1]);
  printf("%s\n", drivers[2].c.manufacturer);
  free(drivers);
  
  xmlCleanupParser();
  exit(EXIT_SUCCESS);
}
