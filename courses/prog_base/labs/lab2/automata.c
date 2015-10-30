#include "automata.h"

struct {
  int state;
  int input;
  enum Operation op;
  int next_state;
} rule_table[] = {
  {1,2,}
};

void step(int moves[], size_t moves_len, int res[], size_t res_len){

}
