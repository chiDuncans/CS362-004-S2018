/**************************************************
 * File Name: cardtest1.c  - Adventurer Card Test
 * CS362_S2018
 * Assignment 4
 * Author: Chieko Duncans
 * Date: 2018-05-12
 * Description: card test for the Adventurer card
 * 	1) set the variables in the game state
 * 	    cards in hand
 * 	    card in deck
 * 	    	Test Case 1) deck card == 2
 * 	    		when user only pick trasure card twice
 * 	    		if not
 * 	    		deck needs to be filled
 * 	    	Test Case 2) deck card > 2
 * 	    		when user draw 2 treasure and 1 other card
 * 	    		if more other card drawn
 * 	    		deck need to be filled
 * 	    	Test Case 3) deck card < 2 
 * 	    		deck needs to be refilled
 * 	    cards in discard
 * 	  - set the first card as adventurer
 * 	2) play adventure
 * 	3) do assert
 * 	4) Check the game state
 *
 * Adventurer Card should do ...
 * 	1) let player draw 2 treasure cards, copper, silver, or gold
 * 	2) All drawn card should be discarded
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

int checkHandCount(int preHand, int _p, struct gameState *_post) {

	if(_post->handCount[_p] != (preHand + 2)){
			printf ("FAILED \n   expected hand count: %d\n", (preHand + 2));
			printf ("   post hand count: %d\n", _post->handCount[_p]);
		return 1;
	}
	else{
		return 0;
	}
}

int checkDeckCount(int preDeck, int _p, struct gameState *_post) {

	if(_post->deckCount[_p] != (preDeck - 2)){
			printf ("FAILED \n   expected deck count: %d\n", (preDeck - 2));
			printf ("   post deck count: %d\n", _post->deckCount[_p]);
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

	int i, j, n, p, deckCount, discardCount, handCount, error;

	int k[10] = {adventurer, council_room, feast, gardens, mine,
		remodel, smithy, village, baron, great_hall};

	struct gameState G;

	error = 0;

	printf ("Testing Adventurer Card.\n");

/*************************************************************
 * Valid Case Tests
 *
 * 	    	Test Case 1) deck card == 2
 * 	    		when user only pick trasure card twice
 * 	    		if not
 * 	    		deck needs to be filled
 * 	    	Test Case 2) deck card > 2
 * 	    		when user draw 2 treasure and 1 other card
 * 	    		if more other card drawn
 * 	    		deck need to be filled
 * 	    	Test Case 3) deck card < 2 
 * 	    		deck needs to be refilled
 * **********************************************************/
	printf ("VALID CASE TESTS.\n");


	// initialize game for valid number of players 2
	n = 2;

	p = n-2; // set player for 0

	// valid case 1, 2, 3
	for(i = 1; i < 4; i++){
	initializeGame(n, k, 3, &G);  // (num of players, kingdomCards[10], randomSeed, game state)
		deckCount = G.deckCount[p];

		// draw cards until deckCount is 1, 2, or 3
		for(j = deckCount; j > i ; j--){
			drawCard(p, &G);
			discardCard((G.handCount[p] - 1), p, &G, 1);  
		}
		deckCount = G.deckCount[p];
		printf("\nUpdated Deck Card Count: %d\n\n", deckCount);
		handCount = G.handCount[p];
		discardCount = G.discardCount[p];

		G.hand[p][(handCount - 1)] = k[0]; // current hand on Adventurer

		checkCardEffectAdventurer(p, &G);
		error += checkHandCount(handCount, p, &G);

		error += checkDeckCount(deckCount, p, &G);
	}

	if(error == 0){
		printf ("ALL TESTS PASSED\n");
	}
	else{

		printf ("Functional Errors: %d\n", error);
	}
	return 0;
}
