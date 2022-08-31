run : main
	./main

main : main.o elevator.o person.o
	gcc -o $@ main.o elevator.o person.o -lncurses

main.o : main.c elevator.h
	gcc -Wall -o $@ -c $<
#	gcc -Wall -c main.c

person.o : person.c person.h
	gcc -Wall -o $@ -c $<
#	gcc -Wall -c person.c

elevator.o : elevator.c elevator.h person.h
	gcc -Wall -o $@ -c $<

clean : 
	rm -f *.o
