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
		printf ("\nVALID CASE TEST %d.\n", testcase);

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
