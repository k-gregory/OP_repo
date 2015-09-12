#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

#define STRIP_LENGTH 1000 * 1000
#define INITIAL_RULES_NUMBER 100

/*First line defines initial strip state
 *Each next  line defines a rule, where
 * first number goes for state id
 * second number goes for matching value
 * third number goes for new value
 * fourth number goes for turing operation id(specified above)
 * fifth number goes for next state id
 *Numbers are separated by " "
 *For example, line  "2 4 0 1 3" goes for
 * 'If state id is 2 and current element is 4,
 *  change it to 0, move left, and set state to 3'
 */
#define INFILE_RULE_FORMAT "%d %d %d %d %d\n"
typedef int strip_el;

/*{{ Turing operations */
bool move_left(strip_el new_val, int next_state);  /* 0 */
bool move_right(strip_el new_val, int next_state); /* 1 */
bool move_none(strip_el new_val, int next_state);  /* 2 */
/*Turing operations }}*/

bool move_left(strip_el new_val, int next_state) { return true; }
bool move_right(strip_el new_val, int next_state) { return true; }
bool move_none(strip_el new_val, int next_state) { return true; }

struct __rule {
  int matching_state;
  strip_el matching_value;
  strip_el new_value;
  bool (*op)(strip_el, strip_el); // Turing operation
  int next_state;
};
typedef struct __rule Rule;

strip_el *strip;
strip_el *current_el;
int current_state;
Rule *rules_table;

void init() {
  FILE *f = fopen("rules.txt", "r");
  int c;

  rules_table = malloc(sizeof(Rule) * INITIAL_RULES_NUMBER);
  Rule *current_rule = rules_table;
  int t_op_id;
  while (fscanf(f, INFILE_RULE_FORMAT, &current_rule->matching_state,
                &current_rule->matching_value, &current_rule->new_value,
                &t_op_id, &current_rule->next_state) != EOF) {
    bool (*t_op)(strip_el, strip_el);
    switch (t_op_id) {
    case '0':
      t_op = move_left;
      break;
    case '1':
      t_op = move_right;
      break;
    case '2':
      t_op = move_none;
      break;
    }
    current_rule->op = t_op;
    current_rule++; // TODO GOING to segfault on >100 rules. Have to realloc rules_table
  }
}

int main() {
  strip = malloc(sizeof(strip_el) * STRIP_LENGTH); /*memory strip*/
  current_el =
      strip + STRIP_LENGTH / 2; /*put the pointer on the middle of the strip*/
  free(strip);
}
