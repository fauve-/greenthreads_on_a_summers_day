#include "gthread.h"



void gtinit(void){
	gtcur = &gttbl[0];
	gtcur->st = Running;
}



void __attribute__((noreturn)) gtret(int ret) {
  if (gtcur != &gttbl[0]) {
    gtcur->st = Unused;
    gtyield();
    assert(!"reachable");
  }
  while (gtyield());
  exit(ret);
}


bool gtyield(void){
  struct gt *p;
  struct gtctx *old, *new;
  
  p = gtcur;
  while (p->st != Ready) {
    if (++p == &gttbl[MaxGThreads]){
      p = &gttbl[0];
    }
    if (p == gtcur){
      return false;
    }
  }
  
  if (gtcur->st != Unused){
    gtcur->st = Ready;
  }
  p->st = Running;
  old = &gtcur->ctx;
  new = &p->ctx;
  gtcur = p;
  gtswtch(old, new);
  return true;
}


void gt_swap(struct gt *old, struct gt* new){
  old->st = Ready;
  new->st = Running;
  gtswtch(&old->ctx,&new->ctx);
}


static void gtstop(void) { gtret(0); }



int gtgo(void (*f)(void)){
  char *stack;
  struct gt *p;
  
  for (p = &gttbl[0];; p++){
    if (p == &gttbl[MaxGThreads]){
      return -1;
    }else if (p->st == Unused){
      break;
    }
  }
  
  stack = malloc(StackSize);
  if (!stack){
    return -1;
  }

  *(uint64_t *)&stack[StackSize -  8] = (uint64_t)gtstop;
  *(uint64_t *)&stack[StackSize - 16] = (uint64_t)f;
  p->ctx.rsp = (uint64_t)&stack[StackSize - 16];
  p->st = Ready;
  
  return 0;
}
