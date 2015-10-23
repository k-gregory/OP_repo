#include <stdio.h>
#include <stdlib.h>

int present[30];
int last=0;

int contains(int n){
  if(last==0)
    return 0;
  for(int* i = present; i< present+last;i++)
    if(*i == n)
      return 1;
  return 0;
}

void add_if_uniq(int n){
  if(!contains(n)){
    present[last++]=n;
  }
}

int main(){
  for(int i=0;i<30;i++)
    add_if_uniq(i%6);

  printf("That's all nums\n");

  for(int* i=present;i<present+last;i++)
    printf("%d ",*i);
  printf("\n%d",last);
}
