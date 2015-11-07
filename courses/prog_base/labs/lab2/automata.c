#include <stdlib.h>

#include "automata.h"

#define LEN(arr) (sizeof(arr)/sizeof((arr)[0]))

struct Rule {
  int state;
  int input;
  int op;
  int next_state;
};
/*{STATE	INPUT	OP_TYPE	ARG	NEXT_STATE}*/
struct Rule rule_table[] = {
    /*STATE=0*/
    {0, 6, POP, 1},
    {0, 10, 1, 1},
    {0, 15, BREAK, 0},
    {0, 105, 6, 0},
    /*STATE=1*/
    {1, 6, POP, 2},
    {1, 10, CONTINUE, 0},
    {1, 15, 2, 2},
    {1, 105, REPEAT, 3},
    /*STATE=2*/
    {2, 10, 4, 3},
    {2, 105, 3, 3},
    /*STATE=3*/
    {3, 6, BREAK, 0},
    {3, 10, 7, 0},
    {3, 15, 5, 2},
    {3, 105, CONTINUE, 3},
};

struct Rule* match_rule(int state, int input){
  for(size_t i = 0; i< LEN(rule_table);i++){
    if(rule_table[i].state == state && rule_table[i].input==input){
      return &rule_table[i];
    }
  }
  return NULL;
}

void step(int moves[], size_t moves_len, int res[], size_t res_len) {
  size_t moves_n, res_n;
  int state = 0;
  moves_n = res_n = 0;

  for(size_t i =0; i< moves_len;i++){
    struct Rule* m_rule = match_rule(state,moves[moves_n]);
    if(m_rule->op >= 0){
      if(res_n<res_len)
	res[res_n++] = m_rule->op;
    }
    else {
      
    }
  }
}
