#include "struct.h"

struct private_s{
  int a;
  int b;
}
;

s_p s_new(){
  return malloc(sizeof(struct private_s));
}

void set_b(s_p s, int val){
  s->b = val;
}

void set_a(s_p s, int val){
  s->a = val;
}

int get_a(s_p s){
  return s->a;
}

int get_b(s_p s){
  return s->b;
}
