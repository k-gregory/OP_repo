#pragma once

#include "univ_person.h"
#include <stdlib.h>

typedef struct univsec_wicket univsec_wicket;

univsec_wicket* univsec_wicket_new();
void univsec_wicket_free(univsec_wicket* w);

void univsec_wicket_pass(univsec_wicket* w, univ_person* p);

size_t univsec_wicket_get_passes(univsec_wicket* w,
				 univ_person** result,
				 size_t max_passes);

