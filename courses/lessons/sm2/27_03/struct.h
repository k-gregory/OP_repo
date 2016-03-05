#pragma once
#include <stdlib.h>
typedef struct private_s* s_p;

s_p s_new();

void set_a(s_p s, int val);
void set_b(s_p s, int val);


int get_a(s_p s);
int get_b(s_p s);
