#include "Printer.h"

#include <libthread/thread.h>
#include <libthread/mutex.h>

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>

#define PRINTER_N_MSG 10

static mutex_t* printer_m;
static thread_t* last_active_thread;
static thread_t* curr_thread_free;

struct Printer {
  char* msg;
  thread_t* thread;
};

void PRINTER_INIT(){
  printer_m = mutex_new();
  last_active_thread = thread_getCurrentThread();
  curr_thread_free = last_active_thread;
}

void PRINTER_DEINIT(){
  mutex_free(printer_m);
  thread_free(curr_thread_free);
}

Printer* printer_new(const char* msg){
  
  Printer* ret = malloc(sizeof(Printer));
 
  ret->msg = malloc(strlen(msg) + 1);
  strcpy(ret->msg, msg);

  ret->thread = NULL;

  return ret;
}

void printer_free(Printer* p){
  mutex_lock(printer_m);
  if(p->thread != NULL){
    thread_terminate(p->thread);
    thread_free(p->thread);
  }
  mutex_unlock(printer_m);
  
  free(p->msg);
  free(p);
}

static void* printer_loop(void* printer){
  Printer* p = printer;

  while(1) {
    mutex_lock(printer_m);
    
    if(thread_equals(last_active_thread, p->thread)){
      mutex_unlock(printer_m);
      continue;
    }

    for(size_t i =  0; i < PRINTER_N_MSG; i++)
      puts(p->msg);
    last_active_thread = p->thread;
    //    fflush(stdout);

    mutex_unlock(printer_m);
  }
  
  assert(0);//Exit forewer loop
  return NULL; //Newer happens
}

void printer_exec(Printer* p){
  thread_t* new_thread;
  mutex_lock(printer_m); //Protect from freeing without stopping the thread
  new_thread = thread_create_args(printer_loop, p);
  p->thread = new_thread;
  mutex_unlock(printer_m);
}
