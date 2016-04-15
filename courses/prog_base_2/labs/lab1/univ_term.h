#pragma once

#include "univ_person.h"

#include <stdlib.h>

typedef enum {
  UNIV_TERM_S_OK,
  UNIV_TERM_S_TOOMANY_OUTPUT,
} univ_term_status;

typedef struct univ_term univ_term;

#define UNIV_TERM_MAX_OUTPUT_NUMBER 20
univ_term* univ_term_new(unsigned int output_number,
			 unsigned int term_number,
			 univ_person_category c);
void univ_term_free(univ_term* t);

/**
Sets categories of persons to output.
Multiple categories can be set by binary OR |
\param c Categories for output
 */
void univ_term_set_categories(univ_term* t,univ_person_category c);
void univ_term_display(univ_term* t);

/**
Sets how many passers to display on screen
\param n Number of passers to display
 */
void univ_term_set_output_number(univ_term *t, unsigned int n);

/**
Sends some passers to terminal
\param[in] passers_arr array of persons who passed wicket
\param[in] len number of passers
 */
void univ_term_send_passers(univ_term *t,
			    univ_person **passers_arr,
			    size_t len);

void univ_term_display(univ_term* t);

univ_term_status univ_term_get_error(); //FIXME: Thread-safety sucks
