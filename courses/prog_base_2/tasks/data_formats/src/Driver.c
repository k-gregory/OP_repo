#include "Driver.h"

#include <libxml/tree.h>

#include <stdlib.h>
#include <string.h>

static void print(xmlNode* node, int space_c){
  xmlNode* n;
  char* buff = malloc(space_c+1);
  for(int i =0; i< space_c; i++)
    buff[i] = ' ';
  buff[space_c] = '\0';
  
  for(n = node; n != NULL; n = n->next){
    printf("%s NODE: %d \"%s\" %s\n",buff, n->line, n->name, n->content);
    if(n->children) print(n->children,space_c + 1);
  }
  free(buff);
}

static int driver_from_xml(Driver* d, xmlNode* node){
  
}

unsigned long drivers_parse_from_xml_file(Driver** d, const char* filename){
  xmlDoc* doc;
  xmlNode* xml_root;
  xmlNode* curr_driver;
  unsigned long n_drivers;
  unsigned int i;

  *d = NULL;

  doc = xmlReadFile(filename, NULL, 0);
  if(doc == NULL) goto PARSE_ERROR;
  xml_root = xmlDocGetRootElement(doc);
  n_drivers = xmlChildElementCount(xml_root);
  
  *d = malloc(sizeof(Driver) * n_drivers);

  for(i=0,curr_driver = xml_root->xmlChildrenNode;
      curr_driver != NULL;
      curr_driver = curr_driver->next,i++){
    int driver_parse_res;
    driver_parse_res = driver_from_xml(
				       &((*d)[i]),
				       curr_driver
				       );
    if(driver_parse_res == 0) goto PARSE_ERROR;
  }
  
  xmlFreeDoc(doc);
  return 1;
  return n_drivers;
  
 PARSE_ERROR:
  xmlFreeDoc(doc);
  free(*d);
  *d = NULL;
  return 0;
}
