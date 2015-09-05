#ifndef _GTHREAD_H_
#define  _GTHREAD_H_
#include <assert.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>



struct gt {
  struct gtctx {
    uint64_t rsp;
    uint64_t r15;
    uint64_t r14;
    uint64_t r13;
    uint64_t r12;
    uint64_t rbx;
    uint64_t rbp;
  } ctx;
  enum {
    Unused,
    Running,
    Ready,
    Waiting,
  } st;
};


void gtinit(void);
void gtret(int ret);
void gtswtch(struct gtctx *old, struct gtctx *new);
bool gtyield(void);
static void gtstop(void);
int gtgo(void (*f)(void));
void gt_swap(struct gt *old, struct gt* new);


enum {
	MaxGThreads = 8,
	StackSize = 0x400000,
};

struct gt gttbl[MaxGThreads];
struct gt *gtcur;


#endif
