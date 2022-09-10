a.out: main.o certamen.o
	gcc -g -Wall main.o certamen.o
	make clean

main.o: main.c certamen.h
	gcc -g -Wall -c main.c

certamen.o: certamen.c certamen.h
	gcc -g -Wall -c certamen.c

.PHONY: clean
clean:
	rm -f *.o

.PHONY: cleanall
cleanall:
	rm -f *.o a.out

.PHONY: debug
debug: a.out
	gdb a.out


