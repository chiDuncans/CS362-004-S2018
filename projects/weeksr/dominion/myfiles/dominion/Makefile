CFLAGS = -Wall -fpic -coverage -lm

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

runtests: testDrawCard 
	./testDrawCard &> unittestresult.out
	gcov dominion.c >> unittestresult.out
	cat dominion.c.gcov >> unittestresult.out

#Unit Test
unittest1: unittest1.c dominion.o rngs.o
	gcc  -o  unittest1 -g unittest1.c dominion.o rngs.o $(CFLAGS)

rununittest1: unittest1
	./unittest1 &> unittest1.out
	gcov dominion.c >> unittest1.out
	cat dominion.c.gcov >> unittest1.out

#Adventurer card test
cardtest1: cardtest1.c dominion.o rngs.o
	gcc  -o cardtest1 -g  cardtest1.c dominion.o rngs.o $(CFLAGS)

runcardtest1: cardtest1
	./cardtest1 &> cardtest1.out
	gcov dominion.c >> cardtest1.out
	cat dominion.c.gcov >> cardtest1.out

#Steward card test
testcard2: testcard2.c dominion.o rngs.o
	gcc  -o testcard2 -g  testcard2.c dominion.o rngs.o $(CFLAGS)

runtestcard2: testcard2
	./testcard2 &> testcard2.out
	gcov dominion.c >> testcard2.out
	cat dominion.c.gcov >> testcard2.out

#Smithy card test
cardtest3: cardtest3.c dominion.o rngs.o
	gcc  -o cardtest3 -g  cardtest3.c dominion.o rngs.o $(CFLAGS)

runcardtest3: cardtest3
	./cardtest3 &> cardtest3.out
	gcov dominion.c >> cardtest3.out
	cat dominion.c.gcov >> cardtest3.out

#Adventurer random test
randomTestAdventurer: randomTestAdventurer.c dominion.o rngs.o
	gcc  -o randomTestAdventurer -g  randomTestAdventurer.c dominion.o rngs.o $(CFLAGS)

#Adventurer random test
randomtestadventurer: randomtestadventurer.c dominion.o rngs.o
	gcc  -o randomtestadventurer -g  randomtestadventurer.c dominion.o rngs.o $(CFLAGS)

#Smithy random test
randomtestcard1: randomtestcard1.c dominion.o rngs.o
	gcc  -o randomtestcard1 -g  randomtestcard1.c dominion.o rngs.o $(CFLAGS)

#Steward random test
randomtestcard2: randomtestcard2.c dominion.o rngs.o
	gcc  -o randomtestcard2 -g  randomtestcard2.c dominion.o rngs.o $(CFLAGS)

runrandomtestAdventurer: randomTestAdventurer 
	./randomTestAdventurer &> randomtestadventurer.out
	gcov dominion.c >> randomtestadventurer.out
	cat dominion.c.gcov >> randomtestadventurer.out

runrandomtestadventurer: randomtestadventurer 
	./randomtestadventurer &> randomtestadventurer.out
	gcov dominion.c >> randomtestadventurer.out
	cat dominion.c.gcov >> randomtestadventurer.out

runrandomtest1: randomtestcard1 
	./randomtestcard1 &> randomtestcard1.out 
	gcov dominion.c >> randomtestcard1.out
	cat dominion.c.gcov >> randomtestcard1.out

runrandomtest2: randomtestcard2 
	./randomtestcard2 &> randomtestcard2.out
	gcov dominion.c >> randomtestcard2.out
	cat dominion.c.gcov >> randomtestcard2.out

player: player.c interface.o
	gcc -o player player.c -g  dominion.o rngs.o interface.o $(CFLAGS)

all: playdom player 

clean:
	rm -f *.o playdom.exe playdom player player.exe  *.gcov *.gcda *.gcno *.so *.out testDrawCard testDrawCard.exe
