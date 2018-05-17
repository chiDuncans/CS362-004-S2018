/**************************************************
 * File Name: randomTestAdventurer.c
 * CS362_S2018
 * Assignment 4
 * Author: Chieko Duncans
 * Date: 2018-05-12
 * Description: random test for the Adventurer card
 * 	1) Randomly set the variables in the game state
 * 	  - randomize the number of...
 * 	    cards in hand
 * 	    card in deck
 * 	    cards in discard
 * 	  - set the first card as adventurer
 * 	2) play adventure
 * 	3) do assert
 * 	4) Check the game state
 *
 * Adventurer Card should do ...
 * 	1) let player draw 2 treasure cards, copper, silver, or gold
 * 	2) All drawned card should be discarded
 *
 * Post Condition should be...
 *      1) cards in hand: pre + 2 (2 treasure cards added)
 *      2) cards in deck: - (2 + (post discard - pre discard))
 * ***********************************************/
#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"
#include <time.h>
#include <math.h>

#define DEBUG 0
#define NOISY_TEST 1
#define MAX_TESTS 1000
// #define MAX_PLAYERS 4 //declared in dominion.h
// #define MAX_HAND 500  //declared in dominion.h
// #define MAX_DECK 500  //declared in dominion.h

void checkDrawCard(int p, struct gameState *post) {
	int r;

	r = drawCard (p, post);

	assert (r == 0);
}

int checkHandCount(int preHand, int _p, struct gameState *_post) {

	if(_post->handCount[_p] != (preHand + 2)){
		return 1;
	}
	else{
		return 0;
	}
	// assert(_post->handCount[_p] == (preHand + 2));
}

int checkDeckCount(int preDeck, int _p, struct gameState *_post) {

	if(_post->deckCount[_p] != (preDeck -2)){
		return 1;
	}
	else{
		return 0;
	}

	//   assert(_post->deckCount[_p] == (preDeck -2));
}

int checkDiscardCount(int _p, struct gameState *_post) {

	if(_post->discardCount[_p] != 0){
		return 1;
	}
	else{
		return 0;
	}

	//   assert(_post->discardCount[_p] == 0);
}

int checkTotalCount(int preHand, int preDeck, int _p, struct gameState *_post) {

	if((_post->handCount[_p] + _post->deckCount[_p]) != (preHand + preDeck)){
		return 1;
	}
	else{
		return 0;
	}


	//    assert((_post->handCount[_p] + _post->deckCount[_p]) == (preHand + preDeck));
}

void checkCardEffectAdventurer(int p, struct gameState *post) {
	int r;
	printf ("pre hand count, player 0: %d \n", post->handCount[p]);
	printf ("pre deck count, player 0: %d \n", post->deckCount[p]);
	printf ("pre discard count, player 0: %d \n", post->discardCount[p]);
	r = cardEffectAdventurer(0, post, p, 0); // (drawntreasure = 0, state, currentPlayer, int z = 0)

	assert (r == 0);  // Checking calling the function has error or not

	//  if( r == 0){  // Checking calling the function has error or not
	printf ("post hand count, player 0: %d \n", post->handCount[p]);
	printf ("post deck count, player 0: %d \n", post->deckCount[p]);
	printf ("post discard count, player 0: %d \n", post->discardCount[p]);
	//  }

}

int main () {

	int i, n, r, p, deckCount, discardCount, handCount, error;

	int k[10] = {adventurer, council_room, feast, gardens, mine,
		remodel, smithy, village, baron, great_hall};

	struct gameState G;

	//   srand(time(NULL));
	error = 0;

	printf ("Testing Adventurer Card.\n");

	printf ("RANDOM TESTS.\n");

	SelectStream(2);
	PutSeed(3);

	// initialize game for valid number of players, 2 - 4
	for(n = 2; n <= MAX_PLAYERS; n++){



		p = n-2; // player
		initializeGame(n, k, 1, &G);


		// for each players, do random test for MAX test times
		//added

		for(i = 0; i < MAX_TESTS; i++){
			G.deckCount[p] = floor(Random() * 10) + 5;
			G.discardCount[p] = floor(Random() * 10) + 5;
			G.handCount[p] = floor(Random() * 5);
			//added end
			handCount = G.handCount[p];
			deckCount = G.deckCount[p];
			discardCount = G.discardCount[p];
			//  printf ("pre hand count, player 0: %d \n", G.handCount[p]);
			//  printf ("pre deck count, player 0: %d \n", G.deckCount[p]);
			//  printf ("pre discard count, player 0: %d \n", G.discardCount[p]);
			//  cardEffectAdventurer(0, &G, p, 0); // (drawntreasure = 0, state, currentPlayer, int z = 0)
			checkCardEffectAdventurer(p, &G);

			// to catch number of error, following checks are modified
			/*
			   checkHandCount(handCount, p, &G);
			   checkDeckCount(deckCount, p, &G);
			   checkDiscardCount(p, &G);
			   checkTotalCount(handCount, deckCount, p, &G);
			   */  
			if(checkHandCount(handCount, p, &G) != 0){ error++; }
			//error = error + checkDeckCount(deckCount, p, &G);
			//error = error + checkDiscardCount(p, &G);
			//error = error + checkTotalCount(handCount, deckCount, p, &G);
		}
	} 

	if(error == 0){
		printf ("ALL TESTS PASSED\n");
	}
	else{

		printf ("Functional Errors: %d\n", error);
	}
	return 0;
}
