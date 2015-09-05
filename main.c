#include "gthread.h"
#include "semaphore.h"

semaphore* sema;

void f(void) {
  static int x;
  int i, id;  
  id = ++x;
  for (i = 0; i < 10; i++) {
    gtyield();
  }
  printf("%d %d\n", id, i);
}

void g(void){
  printf("g awaiting\n");
  wait(sema);
  printf("g done waiting\n");  
}

void h(void){
  printf("h started\n");
  printf("h gonna signal\n");
  signal(sema);
  printf("h execution returns!\n");
}


//uncomment those f's and find that we'll return before all gts have finished
//a mystery to uncover!

int main(void){
  sema = new_sema(1);
  gtinit();
  gtgo(g);
  gtgo(g);
  gtgo(g);
  //gtgo(f);
  gtgo(h);
  gtgo(h);
  //  gtgo(f);
  gtgo(h);
  gtgo(h);  
  gtret(1);
}
