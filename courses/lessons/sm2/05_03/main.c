#include "shared.h"
#include "dlfcn.h"
#include <stdlib.h>
#include <stdio.h>

void (*s_f)();

int main(){
  void* hdl = dlopen("libshared.so",RTLD_LAZY);
  if(!hdl){
    fputs("Can't load lib",stderr);
    return EXIT_FAILURE;
  }
  s_f = dlsym(hdl,"shared_f");
  if(!s_f){
    fputs("shared_f not found",stderr);
    return EXIT_FAILURE;
  }
  s_f();

  return EXIT_SUCCESS;
}
