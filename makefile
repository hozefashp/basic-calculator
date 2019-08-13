project : infix.o stack.o cstack.o number.o
	cc infix.o stack.o cstack.o number.o -o project
infix.o : infix.c stack.h cstack.h
	cc -c infix.c
stack.o : stack.h number.h
	cc -c stack.c
cstack.o : cstack.c cstack.h
	cc -c cstack.c
number.o : number.c number.h
	cc -c number.c
