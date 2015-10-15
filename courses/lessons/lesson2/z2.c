#include <stdio.h>
#include <stdlib.h>

static inline void swapch(char* a,char* b){
  char t=*a;
  *a=*b;
  *b=t;
}

void m2(char* m,int l){
  char* b;
  char* e;
  for(b=m,e=m+l-1;b<e;b++,e--)
    swapch(b,e);
}

int main(void) {
  int n;
  scanf("%d\n",&n);
  char* c = malloc(sizeof(char)*n);
  char* t =c;
  for(int i =0;i<n;i++)
    scanf("%c",t++);
  m2(c,n);
  t=c;
  for(int i=0;i<n;i++)
    printf("%c\n",*t++);
  return 0;
}
