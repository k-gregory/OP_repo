#include "Driver.h"

#include <libxml/tree.h>

#include <stdlib.h>
#include <string.h>
#include <time.h>

static int car_from_xml(Car* c, xmlNode* node){
  char* data;
  int manufacturer_set,model_set;
  manufacturer_set = model_set = 0;
  for(node = node->children;node!=NULL; node = node->next){
    if(!xmlStrcmp(node->name,(xmlChar*)"manufacturer")){
      manufacturer_set = 1;
      data =(char*) xmlNodeGetContent(node);
      strcpy(c->manufacturer, data);
      xmlFree(data);
      continue;
    }
    if(!xmlStrcmp(node->name,(xmlChar*)"model")){
      model_set = 1;
      data =(char*) xmlNodeGetContent(node);
      strcpy(c->model, data);
      xmlFree(data);
      continue;
    }
  }
  if(manufacturer_set && model_set){
    return 1;
  } else return 0;
}

static int driver_from_xml(Driver* d, xmlNode* node){
  int car_set,avgSpeed_set,kmFare_set,nsat_set,nunsat_set,hired_set;
  char* data;
  car_set = avgSpeed_set = kmFare_set = nsat_set = nunsat_set = hired_set = 0;
  for(node = node->children; node != NULL; node = node->next){
    if(!xmlStrcmp(node->name,(xmlChar*) "car")){
      car_set = car_from_xml(&d->c, node);
      continue;
    }
    if(!xmlStrcmp(node->name,(xmlChar*) "averageSpeedKm")){
      data = (char*) xmlNodeGetContent(node);
      avgSpeed_set = sscanf(data,"%lf",&d->averageSpeedKm);
      xmlFree(data);
      continue;
    }
    if(!xmlStrcmp(node->name,(xmlChar*) "kmFare")){
      data = (char*) xmlNodeGetContent(node);
      kmFare_set = sscanf(data,"%lf",&d->kmFare);
      xmlFree(data);
      continue;
    }
    if(!xmlStrcmp(node->name,(xmlChar*) "satisfiedClients")){
      data = (char*) xmlNodeGetContent(node);
      nsat_set = sscanf(data,"%d",&d->satisfiedClients);
      xmlFree(data);
      continue;
    }
    if(!xmlStrcmp(node->name,(xmlChar*) "unsatisfiedClients")){
      data = (char*) xmlNodeGetContent(node);
      nunsat_set = sscanf(data,"%d",&d->unsatisfiedClients);
      xmlFree(data);
      continue;
    }
    if(!xmlStrcmp(node->name,(xmlChar*) "hiredAt")){
      struct tm hired_at;
      memset(&hired_at, 0, sizeof(hired_at));
      
      data = (char*) xmlNodeGetContent(node);
      hired_set = sscanf(data,"%d-%d-%d",&hired_at.tm_year,
			 &hired_at.tm_mon, &hired_at.tm_mday);
      hired_at.tm_mon--;
      d->hired_at = mktime(&hired_at);
      xmlFree(data);
      continue;
    }
  }
  if(car_set&&avgSpeed_set&&kmFare_set&&nsat_set&&nunsat_set&&hired_set)
    return 1;
  else return 0;
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
  
  *d = malloc(sizeof(Driver) * n_drivers * 3); //TODO: Fix 3

  for(i=0,curr_driver = xml_root->xmlChildrenNode;
      curr_driver != NULL;
      curr_driver = curr_driver->next){
    int driver_parse_res;
    if(!xmlStrcmp(curr_driver->name,(xmlChar*) "driver")){
    driver_parse_res = driver_from_xml(
				       &((*d)[i]),
				       curr_driver
				       );
    if(driver_parse_res == 0) goto PARSE_ERROR;
    i++;
    }
  }
  
  xmlFreeDoc(doc);
  return i;
  
 PARSE_ERROR:
  xmlFreeDoc(doc);
  free(*d);
  *d = NULL;
  return 0;
}
