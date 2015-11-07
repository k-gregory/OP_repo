#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "proc.h"

char *process(char *resultStr, const char *textLines[], int linesNum,
              const char *extraStr) {
  size_t i,j;
  size_t co;
  size_t extra_str_len = strlen(extraStr);

  for (i = 0; i < linesNum; i++) {
    char good = 1;
    for(j = 0; j<extra_str_len;j++)
      if(!strchr(textLines[i],extraStr[j])){
	good = 0;
	break;
      }
    if(good){
      sprintf(resultStr,"%lu %s",i,textLines[i]);
      return resultStr;
    }
  }
  strcpy(resultStr,"No suitable string found!!1");
  return resultStr;
}
