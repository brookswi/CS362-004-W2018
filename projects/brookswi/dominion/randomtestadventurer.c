/***************************************************************************
** Filename: randomtestadventurer.c
** Author: William Ryan Brooks
** Date: 2018-02-18
** Description: Random test for the adventurer card effect in dominion.c
****************************************************************************/
#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <time.h>
#include <math.h>
#include <assert.h>
#include "rngs.h"
#include <stdlib.h>

// Declare struct for keeping track of test outcomes
struct testOutcome
{
    int passDrawCard;
    int failDrawCard;
    int passTreasure;
    int failTreasure;
};

// Function prototype
int testAdventurerCard(int player, int handPos, struct gameState *state, struct testOutcome *testVar);

// Print test results
void printResults(char* title, int passedTests, int failedTests)
{ 
    printf("-----------------------------------------------------------------------------\n");
    printf("   TEST: %s\n", title);
    printf("-----------------------------------------------------------------------------\n");
    printf(" Tests passed: %d\n", passedTests);
    printf(" Tests failed: %d\n\n", failedTests);
}

int main()
{ 
    // TEST: Adventurer card effect
    printf("----------------------------------------------------------------------------------------\n");
    printf("                  RANDOM TESTING: Adventurer card effect\n");
    printf("----------------------------------------------------------------------------------------\n\n");

    // Set test variables 
    struct testOutcome testVar;
    testVar.passDrawCard = 0;
    testVar.failDrawCard = 0;
    testVar.passTreasure = 0;
    testVar.failTreasure = 0;

    // Initialize RNG
    time_t t;
    SelectStream(2);
    PutSeed((unsigned) time(&t));

    int num, player, handPos, i;

    // Create game state
    struct gameState state;

    // Number of tests
    for (num = 0; num < 100000; num++)
    { 
        for (i = 0; i < sizeof(struct gameState); i++)
            ((char*)&state)[i] = floor(Random() * 256);

        // Get random player
        state.numPlayers = MAX_PLAYERS; 
        player = floor(Random() * 4);
        state.whoseTurn = player;
      
        // Get random deck count 
        state.deckCount[player] = floor(Random() * MAX_DECK);
        
        // Add random number of treasure cards to deck 
        int card, randDeckPos;
        int numCards = state.deckCount[player]; 
        for (i = 0; i < numCards; i++)
        { 
            card = rand() % (gold + 1 - copper) + copper;
            randDeckPos = floor(Random() * state.deckCount[player]); 
            state.deck[player][randDeckPos] = card;
        }
             
        // Get random discard count 
        state.discardCount[player] = floor(Random() * (MAX_DECK / 2));
    
        // Add random number of treasure cards to discard 
        int randDiscardPos;
        numCards = state.discardCount[player]; 
        for (i = 0; i < numCards; i++)
        { 
            card = rand() % (gold + 1 - copper) + copper;
            randDiscardPos = floor(Random() * state.discardCount[player]); 
            state.discard[player][randDiscardPos] = card;
        } 

        // Get random hand count 
        state.handCount[player] = floor(Random() * MAX_HAND);
             
        // Get random played card count 
        state.playedCardCount = floor(Random() * MAX_DECK);
      
        // Get random hand position and set to adventurer card 
        handPos = floor(Random() * state.handCount[player]);
        state.hand[player][handPos] = adventurer; 

        // Call test function
        testAdventurerCard(player, handPos, &state, &testVar); 
    }

    printResults("2 cards added to hand and adventurer card discarded", testVar.passDrawCard, testVar.failDrawCard);

    printResults("Exactly 2 more treasure cards are in hand than before", testVar.passTreasure, testVar.failTreasure);

    return 0;   
}


int testAdventurerCard(int player, int handPos, struct gameState *postState, struct testOutcome *testVar)
{
    // Save game state
    struct gameState preState;
    memcpy(&preState, postState, sizeof(struct gameState));

    // Play adventurer card
    cardEffect(adventurer, 0, 0, 0, postState, handPos, 0);

    int gainCards = 2;
    int discardCards = 1;

    // TEST: 2 cards added to hand and adventurer card discarded
 
    if (postState->handCount[player] == preState.handCount[player] + gainCards - discardCards)
    {
        // Print test conditions
        printf("----------------TEST PASSED: 2 cards added to hand and adventurer card discarded---------------\n");
        printf("TEST CONDITIONS\n");
        printf("Player: %d   Hand Count: %d   Deck Count: %d   Discard Count: %d   Hand Position: %d\n", player + 1, preState.handCount[player], preState.deckCount[player], preState.discardCount[player], handPos);
        testVar->passDrawCard++; 
        printf("-----------------------------------------------------------------------------------------------\n");
    }
    else       
    { 
        testVar->failDrawCard++; 
    }   
     
    // TEST: 2 more treasure cards are in hand than before
    
    // Count number of treasure cards in pre hand
    int handCount, preHand = 0, postHand = 0;
    int maxHandCount = preState.handCount[player];
    for (handCount = 0; handCount < maxHandCount; handCount++)
    {
        if (preState.hand[player][handCount] == copper || preState.hand[player][handCount] == silver || preState.hand[player][handCount] == gold) 
            preHand++;
    }
  
    // Count number of treasure cards in post hand
    maxHandCount = postState->handCount[player]; 
    for (handCount = 0; handCount < maxHandCount; handCount++)
    {
        if (postState->hand[player][handCount] == copper || postState->hand[player][handCount] == silver || postState->hand[player][handCount] == gold)    
            postHand++;
    }
 
    // Check if post hand has 2 more treasure cards than pre hand
    if (postHand == preHand + 2)
    {
        // Print test conditions
        printf("-------------------------TEST PASSED: 2 more treasure cards in hand------------------------\n");
        printf("TEST CONDITIONS\n");
        printf("Player: %d   Hand Count: %d   Deck Count: %d   Discard Count: %d   Hand Position: %d\n", player + 1, preState.handCount[player], preState.deckCount[player], preState.discardCount[player], handPos);   
        printf("-------------------------------------------------------------------------------------------\n\n");
        testVar->passTreasure++;         
    }
    else 
    { 
        testVar->failTreasure++; 
    }
           
    return 0;
}






