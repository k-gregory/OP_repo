#include "Driver.h"

#include <libxml2/tree.h>

int driver_parse_from_xml_file(Driver* d, const char* filename){
  xmlDoc* doc;
  xmlNode* xml_root;

  doc = xmlReadFile(filename, NULL, 0);
  
}
