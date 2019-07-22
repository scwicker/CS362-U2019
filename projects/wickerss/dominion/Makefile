CFLAGS= -Wall -fpic -coverage -lm -std=c99

rngs.o: rngs.h rngs.c
	gcc -c rngs.c -g  $(CFLAGS)

dominion.o: dominion.h dominion.c rngs.o
	gcc -c dominion.c -g  $(CFLAGS)

playdom: dominion.o playdom.c
	gcc -o playdom playdom.c -g dominion.o rngs.o $(CFLAGS)
#To run playdom you need to entere: ./playdom <any integer number> like ./playdom 10*/
testDrawCard: testDrawCard.c dominion.o rngs.o
	gcc  -o testDrawCard -g  testDrawCard.c dominion.o rngs.o $(CFLAGS)

badTestDrawCard: badTestDrawCard.c dominion.o rngs.o
	gcc -o badTestDrawCard -g  badTestDrawCard.c dominion.o rngs.o $(CFLAGS)

testBuyCard: testDrawCard.c dominion.o rngs.o
	gcc -o testDrawCard -g  testDrawCard.c dominion.o rngs.o $(CFLAGS)

testAll: dominion.o testSuite.c
	gcc -o testSuite testSuite.c -g  dominion.o rngs.o $(CFLAGS)

interface.o: interface.h interface.c
	gcc -c interface.c -g  $(CFLAGS)

randomtestcard1: randomtestcard1.c dominion.o rngs.o
	gcc -o randomtestcard1 -g randomtestcard1.c dominion.o rngs.o $(CFLAGS)

randomtestcard2: randomtestcard2.c dominion.o rngs.o
	gcc -o randomtestcard2 -g randomtestcard2.c dominion.o rngs.o $(CFLAGS)

randomtestcard3: randomtestcard3.c dominion.o rngs.o
	gcc -o randomtestcard3 -g randomtestcard3.c dominion.o rngs.o $(CFLAGS)

player: player.c interface.o
	gcc -o player player.c -g  dominion.o rngs.o interface.o $(CFLAGS)

unittestresults: randomtestcard1 randomtestcard2 randomtestcard3
	./randomtestcard1 >> unittestresult.out
	gcov randomtestcard1.c >> unittestresult.out
	cat randomtestcard1.c.gcov >> unittestresult.out
	./randomtestcard2 >> unittestresult.out
	gcov randomtestcard2.c >> unittestresult.out
	cat randomtestcard2.c.gcov >> unittestresult.out
	./randomtestcard3 >> unittestresult.out
	gcov randomtestcard3.c >> unittestresult.out
	cat randomtestcard3.c.gcov >> unittestresult.out

all: randomtestcard1 randomtestcard2 randomtestcard3

clean:
	rm -f *.o playdom.exe playdom cardtest1 cardtest2 cardtest3 cardtest4 cardtest5 unittest1 unittest2 unittest3 unittest4 unittest5 player player.exe *.gcov *.gcda *.gcno *.so *.out testDrawCard testDrawCard.exe
