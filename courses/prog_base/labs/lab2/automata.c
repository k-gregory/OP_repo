#include <stdlib.h>
#include <assert.h>

#include "automata.h"

#define LEN(arr) (sizeof(arr) / sizeof((arr)[0]))

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

struct Rule *match_rule(int state, int input) {
  for (size_t i = 0; i < LEN(rule_table); i++) {
    if (rule_table[i].state == state && rule_table[i].input == input) {
      return &rule_table[i];
    }
  }
  return NULL;
}

static size_t run_nonulls(int moves[], size_t moves_len, int res[],
                          size_t res_len) {
  size_t res_n = 0;
  int state = 0;

  for (size_t i = 0; i < moves_len; i++) {
    int input = moves[i];
    struct Rule *m_rule = match_rule(state, input);
    if (m_rule == NULL)
      return res_n;
    if (m_rule->op >= 0) {
      if (res_n < res_len)
        res[res_n++] = m_rule->op;
      else
        return res_n;
    } else {
      switch (m_rule->op) {
      case POP:
        if (res_n < 1)
          return 0;
        res_n--;
        break;
      case BREAK:
        return res_n;
        break;
      case REPEAT:
        i--;
        break;
      case CONTINUE:
        break;
      default:
        assert(1 == 2); /*This shall newar hapen*/
        return res_n;
        break;
      }
    }
    state = m_rule->next_state;
  }
  return res_n;
}
size_t run(int moves[], size_t moves_len, int res[], size_t res_len) {
  size_t r = run_nonulls(moves, moves_len, res, res_len);
  for (size_t i = r; i < res_len; i++)
    res[i] = 0;
  return r;
}
