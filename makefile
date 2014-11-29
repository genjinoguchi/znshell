all: main.o prompt.o parser.o run.o check.o
	gcc -o we.out main.o prompt.o parser.o run.o check.o

main.o: main.c prompt.h parser.h
	gcc -c main.c

prompt.o: prompt.c prompt.h parser.h
	gcc -c prompt.c

parser.o: parser.c run.h prompt.h parser.h run.h
	gcc -c parser.c

run.o: run.c parser.c run.h parser.h
	gcc -c run.c

check.o: check.c check.h

clean:
	rm *.o
	rm *~
