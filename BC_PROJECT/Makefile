project: main.o stack.o list.o function1.o gettoken.o infix.o 
	cc -g main.o stack.o list.o function1.o gettoken.o infix.o -o project -lm
main.o: main.c stack.h list.h infix.h
	cc -g -c main.c -Wall
stack.o: stack.c stack.h list.h
	cc -g -c stack.c -Wall
list.o: list.c list.h stack.h
	cc -g -c list.c -Wall
function1.o: function1.c list.h function.h stack.h
	cc -g -c function1.c -Wall
gettoken.o: gettoken.c gettoken.h list.h
	cc -g -c gettoken.c -Wall
infix.o: infix.c infix.h stack.h list.h function.h gettoken.h
	cc -g -c infix.c -Wall

