flags=-g -Wall

main: main.o certamen.o
	gcc $(flags) main.o certamen.o -o main

main.o: main.c certamen.h
	gcc $(flags) -c main.c

certamen.o: certamen.c certamen.h
	gcc $(flags) -c certamen.c

.PHONY: clean
clean:
	rm -f *.o

.PHONY: cleanall
cleanall:
	rm -f *.o main

.PHONY: debug
debug: main
	gdb main

.PHONY: memcheck
memcheck: main
	gdb --command=gdbcmd1 main

.PHONY: run
run: main
	./main