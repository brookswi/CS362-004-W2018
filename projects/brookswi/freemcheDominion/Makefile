CFLAGS = -Wall -fpic -coverage -lm -g

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

randomtestcard1: randomtestcard1.c dominion.c
	gcc -o randomtestcard1 randomtestcard1.c dominion.c rngs.c $(CFLAGS)

randomtestcard2: randomtestcard2.c dominion.c
	gcc -o randomtestcard2 randomtestcard2.c dominion.c rngs.c $(CFLAGS)

randomtestadventurer: randomtestadventurer.c dominion.c
	gcc -o randomtestadventurer randomtestadventurer.c dominion.c rngs.c -g $(CFLAGS)

cardtest1: cardtest1.c dominion.c
	gcc -o cardtest1 dominion.c rngs.c cardtest1.c $(CFLAGS)

cardtest2: cardtest2.c dominion.c
	gcc -o cardtest2 dominion.c rngs.c cardtest2.c $(CFLAGS)

cardtest3: cardtest3.c dominion.c
	gcc -o cardtest3 dominion.c rngs.c cardtest3.c $(CFLAGS)

cardtest4: cardtest4.c dominion.c
	gcc -o cardtest4 dominion.c rngs.c cardtest4.c $(CFLAGS)

unittest1: unittest1.c dominion.c
	gcc -o unittest1 dominion.c rngs.c unittest1.c $(CFLAGS)

unittest2: unittest2.c dominion.c
	gcc -o unittest2 dominion.c rngs.c unittest2.c $(CFLAGS)

unittest3: unittest3.c dominion.c
	gcc -o unittest3 dominion.c rngs.c unittest3.c $(CFLAGS)

unittest4: unittest4.c dominion.c
	gcc -o unittest4 dominion.c rngs.c unittest4.c $(CFLAGS)

testAll: dominion.o testSuite.c
	gcc -o testSuite testSuite.c -g  dominion.o rngs.o $(CFLAGS)

interface.o: interface.h interface.c
	gcc -c interface.c -g  $(CFLAGS)

runtests: testDrawCard 
	./testDrawCard &> unittestresult.out
	gcov dominion.c >> unittestresult.out
	cat dominion.c.gcov >> unittestresult.out

player: player.c interface.o
	gcc -o player player.c -g  dominion.o rngs.o interface.o $(CFLAGS)

all: playdom player testDrawCard testBuyCard badTestDrawCard

clean:
	rm -f *.o playdom.exe playdom player player.exe  *.gcov *.gcda *.gcno *.so *.out testDrawCard testDrawCard.exe



