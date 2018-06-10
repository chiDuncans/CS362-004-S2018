/**************************************************
 * File Name: randomTestAdventurer.c
 * CS362_S2018
 * Assignment 4
 * Author: Chieko Duncans
 * Date: 2018-05-12
 * Description: random test for the Steward card
 * 	1) Randomly set the variables in the game state
 * 	  - randomize the number of...
 * 	    cards in hand
 * 	    card in deck
 * 	    cards in discard
 * 	  - set the first card as adventurer
 * 	2) play smithy card
 * 	3) do assert
 * 	4) Check the game state
 *
 * council_room Card should do ...
 * 	1) let player do one of following choices
 * 		1-1) draw 2 cards
 * 		1-2) +2 coins
 * 		1-3) trash 2 cards in hand 
 * 	2) then discard card from hand
 *
 * Post Condition should be...
 *      1-1) cards in hand: pre + 2 -1
 *      1-2) or coins +2 and cards in hand: -1
 *      1-3) or cards in hand: -2 -1
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

int checkCoinCount(int preCoin, struct gameState *_post, int _choice1) {

	if(_choice1 == 2){
		if(_post->coins != (preCoin + 2)){
			return 1;
		}
		else{
			return 0;
		}
	}
	else{
		if(_post->coins != preCoin ){
			return 1;
		}
		else{
			return 0;
		}
	
	}
}

int checkHandCount(int preHand, int _p, struct gameState *_post, int _choice1) {

	if(_choice1 == 1){
		if(_post->handCount[_p] != (preHand + 2)){
			return 1;
		}
		else{
			return 0;
		}

	}
	else if(_choice1 == 2){
		if(_post->handCount[_p] != preHand){
			return 1;
		}
		else{
			return 0;
		}

	}
	else{
		if(_post->handCount[_p] != (preHand - 2)){
			return 1;
		}
		else{
			return 0;
		}

	}

}

int checkDeckCount(int preDeck, int _p, struct gameState *_post) {

	if(_post->deckCount[_p] != (preDeck -3)){
		return 1;
	}
	else{
		return 0;
	}

	//   assert(_post->deckCount[_p] == (preDeck -2));
}

int checkDiscardCount(int _p, struct gameState *_post) {

	if(_post->discardCount[_p] != 1){
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

void checkCardEffectSteward(struct gameState *post, int p, int _handPos, int choice1, int choice2, int choice3) {
	int r;
	printf ("pre hand count, player 0: %d \n", post->handCount[p]);
	printf ("pre deck count, player 0: %d \n", post->deckCount[p]);
	printf ("pre discard count, player 0: %d \n", post->discardCount[p]);
	r = cardEffectSteward(post, p, choice1, choice2, choice3, _handPos); 

	assert (r == 0);  // Checking calling the function has error or not

	//  if( r == 0){  // Checking calling the function has error or not
	printf ("post hand count, player 0: %d \n", post->handCount[p]);
	printf ("post deck count, player 0: %d \n", post->deckCount[p]);
	printf ("post discard count, player 0: %d \n", post->discardCount[p]);
	//  }

}


int main () {

	int i, n, r, p, deckCount, discardCount, handCount, handPos, coinCount, error;
	int choice1, choice2, choice3;
	int k[12] = {adventurer, council_room, feast, gardens, mine,
		remodel, smithy, village, baron, great_hall, minion, steward};

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
	  		handPos = G.handCount[p] -1;
			G.hand[p][handPos] = k[11];  // current hand on steward
			//added end
			handCount = G.handCount[p];
			deckCount = G.deckCount[p];
			discardCount = G.discardCount[p];

			G.coins = floor(Random() * 5);
			coinCount = G.coins;
			choice1 = (floor(Random() * 3)) + 1;
			choice2 = (floor(Random() * G.handCount[p])) + 1;
			choice3 = (floor(Random() * G.handCount[p])) + 1;
			//  printf ("pre hand count, player 0: %d \n", G.handCount[p]);
			//  printf ("pre deck count, player 0: %d \n", G.deckCount[p]);
			//  printf ("pre discard count, player 0: %d \n", G.discardCount[p]);


			checkCardEffectSteward(&G, p, handPos, choice1, choice2, choice3);
			// to catch number of error, following checks are modified
			/*
			   checkHandCount(handCount, p, &G);
			   checkDeckCount(deckCount, p, &G);
			   checkDiscardCount(p, &G);
			   checkTotalCount(handCount, deckCount, p, &G);
			   */  
			if(checkHandCount(handCount, p, &G, choice1) != 0){ error++; }
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
