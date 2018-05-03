CFLAGS = -Wall -fpic -coverage -lm -std=c99

default: tests.out

tests.out: unittest1.c dominion.c
	echo "Result for running dominion unit tests: " > tests.out
	
	echo "unittest1.c:" >> tests.out
	gcc -o unittest1 rngs.c dominion.c unittest1.c %(CFLAGS)
	./unittest1 >> tests.out
	gcov dominion.c >> tests.out

clean:
	rm -f *.o  *.gcov *.gcda *.gcno *.so *.out 
