#pragma once

#include "univ_person.h"
#include <stdlib.h>

typedef enum {
  UNIVSEC_WICKET_S_OK,
  UNIVSEC_WICKET_S_BADPOLLOUT,
} univsec_wicket_status;

typedef struct univsec_wicket univsec_wicket;

univsec_wicket* univsec_wicket_new();
void univsec_wicket_free(univsec_wicket* w);

void univsec_wicket_pass(univsec_wicket* w, univ_person* p);

size_t univsec_wicket_get_passes(univsec_wicket* w,
				 univ_person** result,
				 size_t max_passes);

univsec_wicket_status univsec_wicket_get_error(); //FIXME: thread-safety sucks
