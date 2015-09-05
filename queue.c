#include "queue.h"
#include <stdlib.h>

queue* new_queue(){
  queue* q = malloc(sizeof(queue));
  q->next = 0;
  q->insert = 1;
  return q;
}

void queue_insert(queue* q,void* to_insert){
  if(q->next == q->insert){
    exit(145);
  }
  int idx = q->insert % Q_MAX_SIZE;
  q->enqueued[idx] = to_insert;
  q->insert++;
}

void* queue_get(queue* q){
  if(q->next == q->insert){
    return NULL;
  }
  q->next++;
  int idx = q->next % Q_MAX_SIZE;
  return q->enqueued[idx];
}


