#ifndef __AUTOMATA_H__
#define __AUTOMATA_H__


#include <stdlib.h>

typedef enum {
  BREAK=-4,
  REPEAT,
  CONTINUE,
  POP
} Operation;

int run(int moves[], size_t moves_len, int res[], size_t res_len);

#endif
