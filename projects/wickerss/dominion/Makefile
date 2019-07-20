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



testUpdateCoins: testUpdateCoins.c dominion.o rngs.o
	gcc -o testUpdateCoins -g  testUpdateCoins.c dominion.o rngs.o $(CFLAGS)

testUnitTest1: unittest1.c dominion.o rngs.o
	gcc -o unittest1 -g unittest1.c dominion.o rngs.o $(CFLAGS)

testUnitTest2: unittest2.c dominion.o rngs.o
	gcc -o unittest2 -g unittest2.c dominion.o rngs.o $(CFLAGS)

testUnitTest3: unittest3.c dominion.o rngs.o
	gcc -o unittest3 -g unittest3.c dominion.o rngs.o $(CFLAGS)

testUnitTest4: unittest4.c dominion.o rngs.o
	gcc -o unittest4 -g unittest4.c dominion.o rngs.o $(CFLAGS)

testUnitTest5: unittest5.c dominion.o rngs.o
	gcc -o unittest5 -g unittest5.c dominion.o rngs.o $(CFLAGS)

testCardTest1: cardtest1.c dominion.o rngs.o
	gcc -o cardtest1 -g cardtest1.c dominion.o rngs.o $(CFLAGS)

testCardTest2: cardtest2.c dominion.o rngs.o
	gcc -o cardtest2 -g cardtest2.c dominion.o rngs.o $(CFLAGS)

testCardTest3: cardtest3.c dominion.o rngs.o
	gcc -o cardtest3 -g cardtest3.c dominion.o rngs.o $(CFLAGS)

testCardTest4: cardtest4.c dominion.o rngs.o
	gcc -o cardtest4 -g cardtest4.c dominion.o rngs.o $(CFLAGS)

testCardTest5: cardtest5.c dominion.o rngs.o
	gcc -o cardtest5 -g cardtest5.c dominion.o rngs.o $(CFLAGS)

player: player.c interface.o
	gcc -o player player.c -g  dominion.o rngs.o interface.o $(CFLAGS)

unittestresults: testUnitTest1 testUnitTest2 testUnitTest3 testUnitTest4 testUnitTest5 testCardTest1 testCardTest2 testCardTest3 testCardTest4 testCardTest5 
	./unittest1 >> unittestresult.out
	gcov unittest1.c >> unittestresult.out
	cat unittest1.c.gcov >> unittestresult.out
	./unittest2 >> unittestresult.out
	gcov unittest2.c >> unittestresult.out
	cat unittest2.c.gcov >> unittestresult.out
	./unittest3 >> unittestresult.out
	gcov unittest3.c >> unittestresult.out
	cat unittest3.c.gcov >> unittestresult.out
	./unittest4 >> unittestresult.out
	gcov unittest4.c >> unittestresult.out
	cat unittest4.c.gcov >> unittestresult.out
	./unittest5 >> unittestresult.out
	gcov unittest5.c >> unittestresult.out
	cat unittest5.c.gcov >> unittestresult.out
	./cardtest1 >> unittestresult.out
	gcov cardtest1.c >> unittestresult.out
	cat cardtest1.c.gcov >> unittestresult.out
	./cardtest2 >> unittestresult.out
	gcov cardtest2.c >> unittestresult.out
	cat cardtest2.c.gcov >> unittestresult.out
	./cardtest3 >> unittestresult.out
	gcov cardtest3.c >> unittestresult.out
	cat cardtest3.c.gcov >> unittestresult.out
	./cardtest4 >> unittestresult.out
	gcov cardtest4.c >> unittestresult.out
	cat cardtest4.c.gcov >> unittestresult.out
	./cardtest5 >> unittestresult.out
	gcov cardtest5.c >> unittestresult.out
	cat cardtest5.c.gcov >> unittestresult.out

all: playdom player testUpdateCoins testUnitTest1 testUnitTest2 testUnitTest3 testUnitTest4 testUnitTest5 testCardTest1 testCardTest2 testCardTest3 testCardTest4 testCardTest5

clean:
	rm -f *.o playdom.exe playdom cardtest1 cardtest2 cardtest3 cardtest4 cardtest5 unittest1 unittest2 unittest3 unittest4 unittest5 player player.exe  *.gcov *.gcda *.gcno *.so *.out testDrawCard testDrawCard.exe
