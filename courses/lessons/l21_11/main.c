#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define LEN(arr) (sizeof(arr)/sizeof((arr)[0]))

int main(int argc, char* argv[]){
  int n,m;
  double sum = 0;
  char buff[1024];

  if(argc!=2)
    return EXIT_FAILURE;
  FILE* fd = fopen(argv[1],"r");

  fgets(buff,LEN(buff),fd);
  sscanf(buff,"%d %d",&n, &m);
  printf("Reading %d lines by %d chars\n", n, m);
  for(int  i =0; i< n; i++){
    double d;
    fgets(buff,LEN(buff),fd);
    char* s;
    s=strtok(buff," ");
    while(s!=NULL){
      sscanf(s,"%lf",&d);
      sum+=d;
      s=strtok(NULL," ");
    }
  }
  printf("\nsum is: %lf\n",sum);
  fclose(fd);
  return EXIT_SUCCESS;
}
