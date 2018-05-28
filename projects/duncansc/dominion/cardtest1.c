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
 *      Test Case 1, 2, 3: 
 *      Deck > 2, 
 *      all deck cards are 1)"copper" 2)"silver 3)"gold"
 *      	1) cards in hand: pre + 2 -1 (2 treasure cards added, 1 adven card discarded)
 *      	2) cards in deck: - 2
 *
 *      Test Case 4, 5, 6: 
 *      Deck > 2, 
 *      1 deck card is  4)"copper" 5)"silver 6)"gold"
 *      Rest of the deck card is NOT treasure card
 *      1 discarded card is treasure card
 *      	1) cards in hand: pre + 2 -1 (2 treasure cards added, 1 adven card discarded)
 *      	2) cards in deck: 0
 *
 *      Test Case 7: 
 *      Deck = 2, 
 *      1 deck card is  4)"copper" 5)"silver 6)"gold"
 *      Another deck card is NOT treasure card
 *      1 discarded card is treasure card
 *      	1) cards in hand: pre + 1 - 1 (1 treasure cards added, 1 adven card discarded)
 *      	2) cards in deck: 0
 *
 *	Test Case 8:
 *	Deck = 0,
 *	discarded card > 2
 *	2 discarded card is treaure card. 
 *	Other cards are non treasure.
 *      	1) cards in hand: pre + 2 -1 (2 treasure cards added, 1 adven card discarded)
 *      	2) cards in deck: 0
 *
 *	Test Case 9:
 *	Deck = 0,
 *	discarded card > 2
 *	no treasure card in discarded pile
 *      	1) cards in hand: pre -1 ( 1 adventurer card discarded)
 *      	2) cards in deck: 0 
 *
 *    
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
	
void setTreasure(int p, struct gameState *_post, int count, int treasureType){
 	int i;
	
	for(i = 0; i < count; i++){
		_post->deck[p][i] = treasureType;
	}
	
}

void setTreasureInDiscard(int p, struct gameState *_post, int count, int treasureType){
 	int i;
	
	for(i = 0; i < count; i++){
		_post->discard[p][i] = treasureType;
		_post->discardCount[p]++;
	}
	
}

int checkHandCount(int preHand, int _p, struct gameState *_post, int _preTreasureHand, int _preTreasureDiscard) {

	int expected;

	if(_preTreasureHand >= 2){ 
		expected = (preHand + 2 - 1);
	}
	else if(_preTreasureHand = 1){
		if(_preTreasureDiscard >= 1){
			expected = (preHand + 2 - 1);
		}
		else{
			expected = (preHand + 1 - 1);
		}
	}
	else{
		if(_preTreasureDiscard >= 2){
			expected = (preHand + 2 - 1);
		}
		else if(_preTreasureDiscard = 1){
			expected = (preHand + 1 - 1);
		}
		else{
			expected = (preHand - 1);
		}
	}

	//if(_post->handCount[_p] != (preHand + 2 - 1)){
	if(_post->handCount[_p] != expected){
		//	printf ("FAILED \n   expected hand count: %d\n", (preHand + 2 - 1));
			printf ("FAILED \n   expected hand count: %d\n", expected);
			printf ("   post hand count: %d\n", _post->handCount[_p]);
		return 1;
	}
	else{
		return 0;
	}
}

int checkDeckCount(int preDeck, int _p, struct gameState *_post, int _preTreasureHand, int _preTreasureDiscard, int preDiscard) {

	int expected;

	if(_preTreasureHand >= 2){ 
		expected = (preDeck - 2 - (_post->discardCount[_p] - preDiscard));
	}
	else if(_preTreasureHand = 1){
		if(_preTreasureDiscard >= 1){
			expected = 0; //(0 + (preDiscard - _post->discardCount[_p] - 1));
		}
		else{
			expected = 0;
		}
	}
	else{
		if(_preTreasureDiscard >= 2){
			expected = 0; //(preDiscard - _post->discardCount[_p] - 2);
		}
		else if(_preTreasureDiscard = 1){
			expected = 0;
		}
		else{
			expected = 0;
		}
	}
	if(_post->deckCount[_p] != expected){
			printf ("FAILED \n   expected deck count: %d\n", expected);
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

void checkCardEffectAdventurer(int p, struct gameState *post, int handPos) {
	int r;
	int temphand[MAX_HAND]; // fixed list #3
	printf ("pre hand count, player 0: %d \n", post->handCount[p]);
	printf ("pre deck count, player 0: %d \n", post->deckCount[p]);
	printf ("pre discard count, player 0: %d \n", post->discardCount[p]);
	
	// fixed list #3
	//r = cardEffectAdventurer(0, post, p, 0); // (drawntreasure = 0, state, currentPlayer, int z = 0)
	r = playAdventurer(0, p, 0, temphand, post, handPos);
	assert (r == 0);  // Checking calling the function has error or not

	//  if( r == 0){  // Checking calling the function has error or not
	printf ("post hand count, player 0: %d \n", post->handCount[p]);
	printf ("post deck count, player 0: %d \n", post->deckCount[p]);
	printf ("post discard count, player 0: %d \n", post->discardCount[p]);
	//  }

}

int main () {

	int n, p, deckCount, discardCount, handCount, error, testcase, treasureType, treasureCountDeck, treasureCountDiscard;

	int k[10] = {adventurer, council_room, feast, gardens, mine,
		remodel, smithy, village, baron, great_hall};

	struct gameState G;

	error = 0;

	printf ("Testing Adventurer Card.\n");

	/*************************************************************
	 * Valid Case Tests
 	 *      Test Case 1, 2, 3: 
 	 *      Deck > 2, 
	 *      all deck cards are 1)"copper" 2)"silver 3)"gold"
 	 *      	1) cards in hand: pre + 2 -1 (2 treasure cards added, 1 adven card discarded)
  	 *      	2) cards in deck: - 2
	 *
	 * **********************************************************/
	printf ("VALID CASE TESTS.\n");


	// initialize game for valid number of players 2
	n = 2;

	p = n-2; // set player for 0

	testcase = 1;
	treasureType = copper; //testcase 1: copper, 2: silver, 3: gold
	for(testcase = 1; testcase < 4; testcase++){ 
		printf ("\nVALID CASE TEST %d.\n", testcase);

		treasureCountDeck = 0;
		treasureCountDiscard = 0;
		initializeGame(n, k, 3, &G);  // (num of players, kingdomCards[10], randomSeed, game state)

		setTreasure(p, &G, G.deckCount[p], treasureType++);  // set and increment the treasureType 
		treasureCountDeck = G.deckCount[p];	
		treasureCountDiscard = 0;	
	
		deckCount = G.deckCount[p];
		printf("\nUpdated Deck Card Count: %d\n\n", deckCount);
		handCount = G.handCount[p];
		discardCount = G.discardCount[p];

		G.hand[p][(handCount - 1)] = k[0]; // current hand on Adventurer

		// fixed list #3
		//checkCardEffectAdventurer(p, &G);
		checkCardEffectAdventurer(p, &G, (handCount - 1));
		error += checkHandCount(handCount, p, &G, treasureCountDeck, treasureCountDiscard);

		error += checkDeckCount(deckCount, p, &G, treasureCountDeck, treasureCountDiscard, discardCount);
	}
 
	/************************************************************** 
	* Test Case 4, 5, 6: 
 	*      Deck > 2, 
 	*      1 deck card is  4)"copper" 5)"silver 6)"gold"
 	*      Rest of the deck card is NOT treasure card
	 *      1 discarded card is treasure card
 	*      	1) cards in hand: pre + 2 -1 (2 treasure cards added, 1 adven card discarded)
 	*      	2) cards in deck: 0
 	*************************************************************/

	testcase = 4;
	treasureType = copper; //testcase 1: copper, 2: silver, 3: gold
	for(testcase = 4; testcase < 7; testcase++){ 
		printf ("VALID CASE TEST %d.\n", testcase);

		initializeGame(n, k, 3, &G);  // (num of players, kingdomCards[10], randomSeed, game state)

		setTreasure(p, &G, 1, treasureType++);  // set 1 deck card and increment the treasureType 
		treasureCountDeck = 1;	
		setTreasureInDiscard(p, &G, 1, treasureType++);  // set 1 deck card and increment the treasureType 
		treasureCountDiscard = 1;	

		deckCount = G.deckCount[p];
		printf("\nUpdated Deck Card Count: %d\n\n", deckCount);
		handCount = G.handCount[p];
		discardCount = G.discardCount[p];

		G.hand[p][(handCount - 1)] = k[0]; // current hand on Adventurer

		// fixed list #3
		//checkCardEffectAdventurer(p, &G);
		checkCardEffectAdventurer(p, &G, (handCount - 1));
		error += checkHandCount(handCount, p, &G, treasureCountDeck, treasureCountDiscard);

		error += checkDeckCount(deckCount, p, &G, treasureCountDeck, treasureCountDiscard, discardCount);
	}

/*
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

		// fixed list #3
		//checkCardEffectAdventurer(p, &G);
		checkCardEffectAdventurer(p, &G, (handCount - 1));
		error += checkHandCount(handCount, p, &G);

		error += checkDeckCount(deckCount, p, &G);
	}
*/
	if(error == 0){
		printf ("ALL TESTS PASSED\n");
	}
	else{

		printf ("Functional Errors: %d\n", error);
	}
	return 0;
}
