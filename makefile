all: main.o prompt.o parser.o
	gcc -o we.out main.o prompt.o parser.o

main.o: main.c prompt.h parser.h
	gcc -c main.c

prompt.o: prompt.c prompt.h parser.h
	gcc -c prompt.c

parser.o: parser.c prompt.h parser.h
	gcc -c parser.c

clean:
	rm *.o
	rm *~
