#ifndef _Q_C_
#define _Q_C_

//basically a little circular buffer
#define Q_MAX_SIZE 256

typedef struct{
  int insert;
  int next;
  void* enqueued[Q_MAX_SIZE];
}queue;


void queue_insert(queue* q,void* thingie);
void* queue_get(queue* q);
queue* new_queue();
#endif
