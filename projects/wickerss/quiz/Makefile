CFLAGS= -Wall -fpic -coverage -lm -std=c99
testme: testme.c
	gcc -o testme -g testme.c $(CFLAGS)
all: testme
	./testme >> testresult.out
	gcov testme.c >> gcovresult.out
clean:
	rm -f *.o testme *.gcov *.gcda *.gcno *.so *.out
