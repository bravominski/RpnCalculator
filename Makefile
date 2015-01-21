all : rpn

calculator.o : calculator.c calculator.h
	clang -c calculator.c

rpn : rpn.c calculator.o
	clang -o rpn rpn.c calculator.o -lm

clean:
	rm *.o rpn
