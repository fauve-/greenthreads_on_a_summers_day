#include "semaphore.h"
#include "gthread.h"
#include <stdlib.h>

semaphore* new_sema(long count){
  semaphore* s = malloc(sizeof(semaphore));
  s->waiting = new_queue();
  s->count = count;
  return s;
}

//akin to releasing a semaphore
void signal(semaphore* s){
  struct gt* new;
  s->count++;
  new = queue_get(s->waiting);
  if(new == NULL){
    gtyield();
  }else{
    gt_swap(gtcur,new);
  }
}


//akin to capturing the semaphore
void wait(semaphore* s){
  s->count--;
  if(s->count < 0){
    gtcur->st = Waiting;
    queue_insert(s->waiting,gtcur);
    gtyield();
  }
  return;
}
