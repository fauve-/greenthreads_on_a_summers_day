#ifndef _SEMAPHORE_H_
#define _SEMAPHORE_H_
#include "queue.h"
#include "gthread.h"
typedef struct{
  long count;
  queue* waiting;
}semaphore;

semaphore* new_sema(long count);

void signal(semaphore* s);
void wait(semaphore* s);

#endif
