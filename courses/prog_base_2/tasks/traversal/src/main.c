#include <unistd.h>
#include <fcntl.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#define MAX_FILE_SIZE (10000)
#define MAX_NAME_LENGTH (50)

typedef struct json json_obj;

typedef struct Driver {
  char name[MAX_NAME_LENGTH];
  double avg_speed;
  int64_t working_stage;
} Driver;

Driver* driver_new(){
  Driver* ret = malloc(sizeof(Driver));

  strcpy(ret->name,"");
  ret->avg_speed = 0;
  ret->working_stage = 0;

  return ret;
}

Driver* driver_from_json(json_obj* node){
  Driver* ret;
  json_obj *name, *avg_speed, *working_stage;

  if(!json_object_get_ex(&node, "name", &name) ||
     !json_object_get_ex(&node, "avg_speed", &avg_speed) ||
     !json_object_get_ex(&node, "working_stage", &working_stage))
    return NULL;

  ret = driver_new(); 
  strcpy(ret->name, json_object_get_string(name));
  ret->avg_speed = json_object_get_double(avg_speed);
  ret->working_stage = json_object_get_int64(working_stage);

  return ret;
}

int main(void){
  int json_file_fd;
  json_obj* jobj;
  char* file_buff;

  if((json_file_fd = open("data.json", O_RDONLY))==-1){
    fputs("Can't open file", stderr);
    free(file_buff);
    exit(EXIT_FAILURE);
  }

  file_buff = malloc(MAX_FILE_SIZE);

  if(!read(json_file_fd, file_buff, MAX_FILE_SIZE)){
    fputs("Too big file", stderr);
    free(file_buff);
    exit(EXIT_FAILURE);
  }
  jobj = (json_obj*) json_tokener_parse(file_buff);
  free(file_buff);

  exit(EXIT_SUCCESS);
}
