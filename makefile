main: main.o certamen.o
	gcc -g -Wall main.o certamen.o -o main

main.o: main.c certamen.h
	gcc -g -Wall -c main.c

certamen.o: certamen.c certamen.h
	gcc -g -Wall -c certamen.c

.PHONY: clean
clean:
	rm -f *.o

.PHONY: cleanall
cleanall:
	rm -f *.o main

.PHONY: debug
debug: main
	gdb main

.PHONY: run
run: main
	./main