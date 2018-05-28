/**************************************************
 * File Name: cardtest4.c  - Village Card Test
 * CS362_S2018
 * Assignment 5
 * Author: Chieko Duncans
 * Date: 2018-05-22
 * Description: card tespt for the Village card
 * 	1) set the variables in the game state
 * 	    cards in hand
 * 	    card in deck
 * 	    	Test Case 1) deck card > 0
 * 	    	Test Case 2) deck card = 0 , discard card > 0
 * 	    Either test case 1,or 2, it should successfully draw 1 card
 * 	     	Test Case 3) deck card = 0, discard card = 0
 * 	     	Unable to card draw. only 2 actions are given
 * 	  - set the first card as smithy
 * 	2) play smithy card
 * 	3) do assert
 * 	4) Check the game state
 *
 * Village Card should do ...
 * 	1) let player draw 1 card
 * 	2) player's action count +2
 * 	3) then discard played card from hand
 * 
 * Test Case 1) and 2)
 * Post Condition should be...
 *      1) cards in hand: pre + 1 - 1
 *      2) cards in deck: pre - 1
 *      3) numActions pre + 2
 * Test Case 3)
 * Post Condition should be...
 *      1) cards in hand: pre - 1
 *      2) cards in deck: pre
 *      3) numActions pre + 2
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

int checkHandCount(int preHand, int preDeck, int preDiscard, int _p, struct gameState *_post) {
	
	int expectedH;

	if(preDeck > 0){
		expectedH = preHand + 1 - 1;
	}
	else{
		if(preDiscard > 0){
			expectedH = preHand + 1 - 1;	
		}
		else{
			expectedH = preHand;
		}
	}

	if(_post->handCount[_p] != expectedH){
			printf ("\n  Test Case preDeck: %d, preDiscard: %d\n", preDeck, preDiscard);
			printf ("FAILED \n   expected hand count: %d\n", expectedH);
			printf ("   post hand count: %d\n", _post->handCount[_p]);
		return 1;
	}
	else{
		return 0;
	}
}

int checkDeckCount(int preHand, int preDeck, int preDiscard, int _p, struct gameState *_post) {

	if(_post->deckCount[_p] != (preDeck - 1)){
			printf ("FAILED \n   expected deck count: %d\n", (preDeck - 1));
			printf ("   post deck count: %d\n", _post->deckCount[_p]);
		return 1;
	}
	else{
		return 0;
	}

}

int checkActionCount(int preAction, struct gameState *_post) {

	if(_post->numActions != (preAction + 2)){
			printf ("FAILED \n   expected numActions count: %d\n", (preAction + 2));
			printf ("   post action count: %d\n", _post->numActions);
		return 1;
	}
	else{
		return 0;
	}

}

void checkCardEffectVillage(struct gameState *post, int p, int _handPos) {
	int r;
	printf ("\npre hand count, player %d: %d \n", p, post->handCount[p]);
	printf ("pre deck count, player %d: %d \n", p, post->deckCount[p]);
	printf ("pre numActions count, player %d: %d \n", p, post->numActions);
	r = playVillage(p, post, _handPos); 

	assert (r == 0);  // Checking calling the function has error or not

	//  if( r == 0){  // Checking calling the function has error or not
	printf ("post hand count, player %d %d \n", p, post->handCount[p]);
	printf ("post deck count, player %d: %d \n", p, post->deckCount[p]);
	printf ("post numActions count, player %d: %d \n", p, post->numActions);
	//  }

}


int main () {

	int i, n, p, deckCount, handCount, discardCount, actionCount, handPos, error;

	int k[10] = {adventurer, council_room, feast, gardens, mine,
		remodel, smithy, village, baron, great_hall};

	struct gameState G;

	//   srand(time(NULL));
	error = 0;

	printf ("Testing Village Card.\n");
/***************************************************
 * Valid Case Tests
 * 	    	Test Case 1) deck card > 0
 * 	    	Test Case 2) deck card = 0 , discard card > 0
 * 	     	Test Case 3) deck card = 0, discard card = 0
 * Test Case 1) and 2)
 * Post Condition should be...
 *      1) cards in hand: pre + 1 - 1
 *      2) cards in deck: pre - 1
 *      3) numActions pre - 1 + 2
 * Test Case 3)
 * Post Condition should be...
 *      1) cards in hand: pre - 1
 *      2) cards in deck: pre
 *      3) numActions pre - 1 + 2
 *
 ***************************************************/
	printf ("Valid Card TESTS.\n");

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
			G.hand[p][handPos] = k[6];
			//added end
			handCount = G.handCount[p];
			deckCount = G.deckCount[p];
			discardCount = G.discardCount[p];
			actionCount = G.numActions;
			checkCardEffectVillage(&G, p, handPos);

		error += checkHandCount(handCount, deckCount, discardCount, p, &G);

	//	error += checkDeckCount(handCount, deckCount, p, &G);

		error += checkActionCount(actionCount, &G);
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
