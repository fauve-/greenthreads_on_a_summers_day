all: asm c semaphore queue main bin

bin:
	gcc queue.o main.o gtswtch.o semaphore.o gthread.o  -o thread

main:
	gcc -c main.c -o main.o

c:
	gcc -c gthread.c -o gthread.o
asm:
	gcc -c gtswtch.S -o gtswtch.o

queue:
	gcc -c queue.c -o queue.o

semaphore:
	gcc -c semaphore.c -o semaphore.o

clean:
	rm -f *.o 
