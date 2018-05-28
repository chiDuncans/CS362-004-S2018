/***********************************************
 * File Name: unittest2.c
 * File Created Date: 2018-04-22
 * Last Updated: 2018-04-25
 * CS362-004-S2018
 * Assignment 3
 * Author: Chieko Duncans (duncansc@oregonstate.edu)
 * File Description: unit test 2 program for buyCard test
 * ********************************************/
#include "dominion.h"
#include <stdio.h>
#include <stdlib.h>
#include "rngs.h"

int getCostTest(int cardNum){
  int ret; // return value of int getCost(int cardNumber)
  int costList[] = {
    0, // 0:curse
    2, // 1:estate
    5, // 2:duchy
    8, // 3:province
    0, // 4:copper
    3, // 5:silver
    6, // 6:gold
    6, // 7:adventurer
    5, // 8:council_room
    4, // 9:feast
    4, // 10:garden
    5, // 11:mine
    4, // 12:remodel
    4, // 13:smithy
    3, // 14:village
    4, // 15:baron
    3, // 16:great_hall
    5, // 17:minion
    3, // 18:steward
    5, // 19:tribute
    3, // 20:abnassador
    4, // 21:cutpurse
    2, // 22:embargo
    5, // 23:outpost
    4, // 24:salvager
    4, // 25:sea_hag
    4  // 26:treasure_map
    };

    ret = getCost(cardNum);
    if(cardNum < 0 || cardNum > 26){
      assert(ret == -1); // check return value is -1 or not
    }
    else{  
      assert(ret == costList[cardNum]); // check return value is 0 or above, compare
    }
}

int main (int argc, char** argv) {

  int i; // loop counter
 
  printf ("-------- Card numbers are 0 - 26 \n");
  

  printf ("-------- Test 1: card number 0 - 26 \n");
  for(i=0, i < 27; i++){
    getCostTest(i);
  }

  printf ("-------- Test 2: card number -1 \n");
  getCostTest(-1);

  printf ("-------- Test 3: card number 27 \n");
  getCostTest(27);

  return 0;
}
#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"

#define DEBUG 0
#define NOISY_TEST 1

int checkDrawCard(int p, struct gameState *post) {
  struct gameState pre;
  memcpy (&pre, post, sizeof(struct gameState));

  int r;
  //  printf ("drawCard PRE: p %d HC %d DeC %d DiC %d\n",
  //	  p, pre.handCount[p], pre.deckCount[p], pre.discardCount[p]);
    
  r = drawCard (p, post);

  //printf ("drawCard POST: p %d HC %d DeC %d DiC %d\n",
  //      p, post->handCount[p], post->deckCount[p], post->discardCount[p]);

  if (pre.deckCount[p] > 0) {
    pre.handCount[p]++;
    pre.hand[p][pre.handCount[p]-1] = pre.deck[p][pre.deckCount[p]-1];
    pre.deckCount[p]--;
  } else if (pre.discardCount[p] > 0) {
    memcpy(pre.deck[p], post->deck[p], sizeof(int) * pre.discardCount[p]);
    memcpy(pre.discard[p], post->discard[p], sizeof(int)*pre.discardCount[p]);
    pre.hand[p][post->handCount[p]-1] = post->hand[p][post->handCount[p]-1];
    pre.handCount[p]++;
    pre.deckCount[p] = pre.discardCount[p]-1;
    pre.discardCount[p] = 0;
  }

  assert (r == 0);

  assert(memcmp(&pre, post, sizeof(struct gameState)) == 0);
}

int main () {

  int i, n, r, p, deckCount, discardCount, handCount;

  int k[10] = {adventurer, council_room, feast, gardens, mine,
	       remodel, smithy, village, baron, great_hall};


  struct gameState G;
  
  printf ("Testing buyCard.\n");

  printf ("RANDOM TESTS.\n");

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

  return 0;
}
