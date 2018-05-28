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

#define DEBUG 0
#define NOISY_TEST 1

int checkDrawCard(int p, struct gameState *post) {
  int r;
    
  r = drawCard (p, post);

  assert (r == 0);
}

int checkCardEffectAdventure(int p, struct gameState *post) {
  int r;

  r = cardEffectAdventurer(0, post, p, 0); // (drawntreasure = 0, state, currentPlayer, int z = 0)

  assert (r == 0);  // Checking calling the function has error or not
}

int main () {

  int i, n, r, p, deckCount, discardCount, handCount;

  int k[10] = {adventurer, council_room, feast, gardens, mine,
	       remodel, smithy, village, baron, great_hall};

  struct gameState G;

  printf ("Testing Adventurer Card.\n");

  printf ("RANDOM TESTS.\n");
  
  p = 0;
  initializeGame(2, k, 1, &G);
  printf ("pre hand count, player 0: %d \n", G.handCount[p]);
  printf ("pre deck count, player 0: %d \n", G.deckCount[p]);
  printf ("pre discard count, player 0: %d \n", G.discardCount[p]);
  cardEffectAdventurer(0, &G, p, 0); // (drawntreasure = 0, state, currentPlayer, int z = 0)
  printf ("post hand count, player 0: %d \n", G.handCount[p]);
  printf ("post deck count, player 0: %d \n", G.deckCount[p]);
  printf ("post discard count, player 0: %d \n", G.discardCount[p]);
/*
  SelectStream(2);
  PutSeed(3);

  for (n = 0; n < 2000; n++) {
    for (i = 0; i < sizeof(struct gameState); i++) {
      ((char*)&G)[i] = floor(Random() * 256);
    }
    p = floor(Random() * 2);
    G.deckCount[p] = floor(Random() * MAX_DECK);
    G.discardCount[p] = floor(Random() * MAX_DECK);
    G.handCount[p] = floor(Random() * MAX_HAND);
    checkDrawCard(p, &G);
  }

  printf ("ALL TESTS OK\n");

  exit(0);

  printf ("SIMPLE FIXED TESTS.\n");
  for (p = 0; p < 2; p++) {
    for (deckCount = 0; deckCount < 5; deckCount++) {
      for (discardCount = 0; discardCount < 5; discardCount++) {
	for (handCount = 0; handCount < 5; handCount++) {
	  memset(&G, 23, sizeof(struct gameState)); 
	  r = initializeGame(2, k, 1, &G);
	  G.deckCount[p] = deckCount;
	  memset(G.deck[p], 0, sizeof(int) * deckCount);
	  G.discardCount[p] = discardCount;
	  memset(G.discard[p], 0, sizeof(int) * discardCount);
	  G.handCount[p] = handCount;
	  memset(G.hand[p], 0, sizeof(int) * handCount);
	  checkDrawCard(p, &G);
	}
      }
    }
  }
*/
  return 0;
}
