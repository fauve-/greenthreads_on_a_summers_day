#include "gthread.h"
#include "semaphore.h"

semaphore* sema;



void f(void) {
  static int x;
  int i, id;  
  id = ++x;
  for (i = 0; i < 10; i++) {
    printf("%d %d\n", id, i);
    gtyield();
  } 
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


int main(void){
  sema = new_sema(1);
  gtinit();
  //  gtgo(f);
  //  gtgo(f);
  gtgo(g);
  gtgo(g);
  gtgo(g);
  gtgo(h);
  gtgo(h);
  gtgo(h);
  gtgo(h);  
  gtret(1);
}
