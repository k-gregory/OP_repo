#ifndef __AUTOMATA_H__
#define __AUTOMATA_H__

#include <stdlib.h>

enum OP_type {
  BREAK = -4,
  REPEAT,
  CONTINUE,
  POP,
};

int run(int moves[], size_t moves_len, int res[], size_t res_len);

#endif
