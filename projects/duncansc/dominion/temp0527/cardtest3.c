/**************************************************
 * File Name: cardtest3.c  - Smithy Card Test
 * CS362_S2018
 * Assignment 4
 * Author: Chieko Duncans
 * Date: 2018-05-22
 * Description: card tespt for the Smithy card
 * 	1) set the variables in the game state
 * 	    cards in hand
 * 	    card in deck
 * 	    	Test Case 1) deck card > 3
 * 	    	Test Case 2) deck card = 3
 * 	    	Test Case 3) deck card < 3
 * 	    Either test case 1,2, or 3, it should successfully draw 3 cards
 * 	  - set the first card as smithy
 * 	2) play smithy card
 * 	3) do assert
 * 	4) Check the game state
 *
 * Smithy Card should do ...
 * 	1) let player draw 3 cards
 * 	2) then discard card from hand
 *
 * Post Condition should be...
 *      1) cards in hand: pre + 3 - 1
 *      2) cards in deck: -3
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

	if(_post->handCount[_p] != (preHand + 3 - 1)){
			printf ("FAILED \n   expected hand count: %d\n", (preHand + 3 - 1));
			printf ("   post hand count: %d\n", _post->handCount[_p]);
		return 1;
	}
	else{
		return 0;
	}
}

int checkDeckCount(int preDeck, int _p, struct gameState *_post) {

	if(_post->deckCount[_p] != (preDeck - 3)){
			printf ("FAILED \n   expected deck count: %d\n", (preDeck - 3));
			printf ("   post deck count: %d\n", _post->deckCount[_p]);
		return 1;
	}
	else{
		return 0;
	}

}

void checkCardEffectSmithy(struct gameState *post, int p, int _handPos) {
	int r;
	printf ("\npre hand count, player 0: %d \n", post->handCount[p]);
	printf ("pre deck count, player 0: %d \n", post->deckCount[p]);
//	r = cardEffectSmithy(post, p, _handPos); 
	r = playSmithy(p, post, _handPos); 

	assert (r == 0);  // Checking calling the function has error or not

	//  if( r == 0){  // Checking calling the function has error or not
	printf ("post hand count, player 0: %d \n", post->handCount[p]);
	printf ("post deck count, player 0: %d \n", post->deckCount[p]);
	//  }

}


int main () {

	int i, n, p, deckCount, handCount, handPos, error;

	int k[10] = {adventurer, council_room, feast, gardens, mine,
		remodel, smithy, village, baron, great_hall};

	struct gameState G;

	//   srand(time(NULL));
	error = 0;

	printf ("Testing Smithy Card.\n");
/***************************************************
 * Valid Case Tests
 * 	Draw 3 cards from deck. Boundary Checks
 * 	    	Test Case 1) deck card > 3
 * 	    	Test Case 2) deck card = 3
 * 	    	Test Case 3) deck card < 3 
 * 	    	              AND
 * 	    	             discard card >= 3
 * 	    		When deck card is less than 3,
 * 	    		discarded card pile should be shuffled
 * 	    		then added to deck pile.
 *              Test Case 4) deck card < 3
 *              	      AND
 *              	     deck + discard < 3
 *
 *              	     Then 
 *              	     post hand count should be
 *              	     count of (deck + discard)
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
			//discardCount = G.discardCount[p];
			checkCardEffectSmithy(&G, p, handPos);

		error += checkHandCount(handCount, p, &G);

		error += checkDeckCount(deckCount, p, &G);

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
/*
	for(i = 1; i < 4; i++){
		// n is number of players
		n = 2;
		// initialization with 2 player game
		initializeGame(n, k, 1, &G);

		p = n-2; // player

		handPos = G.handCount[p] -1;
		G.hand[p][handPos] = k[11];  // current hand on steward
		handCount = G.handCount[p];
		deckCount = G.deckCount[p];
		//	discardCount = G.discardCount[p];

		coinCount = G.coins;

		// choice1 is 1, 2, or 3
		choice1 = i;
		choice2 = G.hand[p][1];
		choice3 = G.hand[p][2];
		//  printf ("pre hand count, player 0: %d \n", G.handCount[p]);
		//  printf ("pre deck count, player 0: %d \n", G.deckCount[p]);
		//  printf ("pre discard count, player 0: %d \n", G.discardCount[p]);


		checkCardEffectSteward(&G, p, handPos, choice1, choice2, choice3);

		error += checkHandCount(handCount, p, &G, choice1);

		error += checkDeckCount(deckCount, p, &G, choice1);

		error += checkCoinCount(coinCount, &G, choice1);
		
		printf ("\n");
	}
 

	if(error == 0){
		printf ("ALL TESTS PASSED\n");
	}
	else{

		printf ("Functional Errors: %d\n", error);
	}
	return 0;
}
*/
