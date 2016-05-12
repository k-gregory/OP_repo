#pragma once

typedef struct am_observable am_observable;

typedef void (*am_observable_cb)(void* data, void* event);


am_observable* am_observable_new();

void am_observable_emit(am_observable* o, void* event);

void am_observable_add_observer
(am_observable* o, am_observable_cb h, void* data);
void am_observable_remove_observer
(am_observable* o, am_observable_cb h, void* data);

void am_observable_free(am_observable* o);
