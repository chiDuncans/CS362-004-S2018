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
 * steward Card should do ...
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
			printf ("FAILED \n   expected coin count: %d\n", (preCoin + 2));
			printf ("   post coin count: %d\n", _post->coins);
			return 1;
		}
		else{
			return 0;
		}
	}
	else{
		if(_post->coins != preCoin ){
			printf ("FAILED \n   expected coin count: %d\n", (preCoin + 2));
			printf ("   post coin count: %d\n", _post->coins);
			return 1;
		}
		else{
			return 0;
		}
	
	}
}

int checkHandCount(int preHand, int _p, struct gameState *_post, int _choice1) {

	if(_choice1 == 1){
		if(_post->handCount[_p] != (preHand + 2 - 1)){
			printf ("FAILED \n   expected hand count: %d\n", (preHand + 2 - 1));
			printf ("   post hand count: %d\n", _post->handCount[_p]);
			return 1;
		}
		else{
			return 0;
		}

	}
	else if(_choice1 == 2){
		if(_post->handCount[_p] != (preHand - 1)){
			printf ("FAILED \n   expected hand count: %d\n", (preHand - 1));
			printf ("   post hand count: %d\n", _post->handCount[_p]);
			return 1;
		}
		else{
			return 0;
		}

	}
	else{
		if(_post->handCount[_p] != (preHand - 2 - 1)){
			printf ("FAILED \n   expected hand count: %d\n", (preHand - 2 - 1));
			printf ("   post hand count: %d\n", _post->handCount[_p]);
			return 1;
		}
		else{
			return 0;
		}

	}

}
/*
 * Post Condition should be...
 *      1-1) cards in hand: pre + 2 -1
 *      1-2) or coins +2 and cards in hand: -1
 *      1-3) or cards in hand: -2 -1
 *
 */
int checkDeckCount(int preDeck, int _p, struct gameState *_post, int _choice1) {


	if(_choice1 == 1){
		if(_post->deckCount[_p] != (preDeck -2)){
			printf ("FAILED \n   expected deck count: %d\n", (preDeck - 2));
			printf ("   post deck count: %d\n", _post->deckCount[_p]);
			return 1;
		}
		else{
			return 0;
		}
	}
	else if(_choice1 == 2){
		if(_post->deckCount[_p] != preDeck){
			printf ("FAILED \n   expected deck count: %d\n", preDeck);
			printf ("   post deck count: %d\n", _post->deckCount[_p]);
			return 1;
		}
		else{
			return 0;
		}
	}
	else{
		if(_post->deckCount[_p] != preDeck){
			printf ("FAILED \n   expected deck count: %d\n", preDeck);
			printf ("   post deck count: %d\n", _post->deckCount[_p]);
			return 1;
		}
		else{
			return 0;
		}

	}
/*	if(_post->deckCount[_p] != (preDeck -3)){
		return 1;
	}
	else{
		return 0;
	}
*/
	//   assert(_post->deckCount[_p] == (preDeck -2));
}
/*
int checkDiscardCount(int preDiscard, int _p, struct gameState *_post, int _choice1) {
	
	if(_choice1 == 1){
		if(_post->discardCount[_p] != (preDiscard + 1)){
			return 1;
		}
		else{
			return 0;
		}
	}
	else if(_choice1 == 2){
		if(_post->discardCount[_p] != (preDiscard + 1)){
			return 1;
		}
		else{
			return 0;
		}
	}
	else{
		if(_post->discardCount[_p] != (preDiscard + 2 + 1)){
			return 1;
		}
		else{
			return 0;
		}
	}

	//   assert(_post->discardCount[_p] == 0);
}
*/
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
	printf ("player: %d, choice: %d \n", p, choice1);
	printf ("pre hand count: %d\n", post->handCount[p]);
	printf ("pre deck count: %d \n", post->deckCount[p]);
	printf ("pre coin count: %d\n", post->coins);
	r = cardEffectSteward(post, p, choice1, choice2, choice3, _handPos); 

	assert (r == 0);  // Checking calling the function has error or not

	//  if( r == 0){  // Checking calling the function has error or not
	printf ("post hand count: %d \n", post->handCount[p]);
	printf ("post deck count: %d \n", post->deckCount[p]);
	printf ("post coin count: %d \n", post->coins);
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

	printf ("Testing Steward Card.\n");

/*****************************************************
 * Valid Case Tests
 * 	user choice 1
 *      1-1) cards in hand: pre + 2 -1
 *	should test
 *	deck card >= 2
 *	deck card = 1
 *	deck card = 0
 *
 * 	user choice 2
 *      1-2) or coins +2 and cards in hand: -1
 *      any condition
 *
 *      1-3) or cards in hand: -2 -1
 *      should test 3 cases below
 *      hand card >= 2
 *      or 
 *      hand card = 1
 *      or
 *      hand card = 0
 * 		
 *
 * **************************************************/
	printf ("Valid Case Test\n");

/***************************************************
 * 	Test choice is 1, 2 and 3
 * 	hand, deck, discard,and coins are game starting value
 * *************************************************/
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
