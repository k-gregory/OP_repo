#include "univsec_wicket.h"
#include "univ_person.h"

#define UNIVSEC_WICKET_START_STACKSIZE 10

univsec_wicket_status univsec_wicket_status_;
#define ok_return(ret)                                                         \
  univsec_wicket_status_ = UNIVSEC_WICKET_S_OK;                                \
  return ret;

univsec_wicket_status univsec_wicket_get_error() {
  return univsec_wicket_status_;
}

struct univsec_wicket {
  // It is a stack of passers(Type univ_person*)
  univ_person **passers; // Passers holder
  size_t capacity;
  size_t passers_top;
};

univsec_wicket *univsec_wicket_new() {
  univsec_wicket *ret = malloc(sizeof(struct univsec_wicket));
  ret->passers_top = 1;
  ret->capacity = UNIVSEC_WICKET_START_STACKSIZE;
  ret->passers = malloc(sizeof(univ_person *) * UNIVSEC_WICKET_START_STACKSIZE);
  ok_return(ret);
}

void univsec_wicket_free(univsec_wicket *w) {
  free(w->passers);
  free(w);
}

void univsec_wicket_pass(univsec_wicket *w, univ_person *p) {
  if (w->passers_top == w->capacity) {
    w->capacity = w->capacity * 2 + 1;
    w->passers = realloc(w->passers, w->capacity * sizeof(univ_person *));
  }
  w->passers[w->passers_top++] = p;
}

size_t univsec_wicket_get_passes(univsec_wicket *w, univ_person **result,
                                 size_t max_passes) {
  if (result == NULL) {
    univsec_wicket_status_ = UNIVSEC_WICKET_S_BADPOLLOUT;
    return 0;
  }

  size_t to_write = max_passes;
  if (w->passers_top - 1 < max_passes)
    to_write = w->passers_top - 1;

  for (size_t i = 0; i < to_write; i++) {
    result[i] = w->passers[w->passers_top - i -1];
  }

  w->passers_top -= to_write;

  ok_return(to_write);
}
