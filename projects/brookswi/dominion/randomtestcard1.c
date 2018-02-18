/***************************************************************************
** Filename: randomtestcard1.c
** Author: William Ryan Brooks
** Date: 2018-02-18
** Description: Random test for the smithy card effect in dominion.c
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
    int passDiscardCard;
    int failDiscardCard;
};

// Function prototype
int testSmithyCard(int player, int handPos, struct gameState *state, struct testOutcome *testVar);

// Print test results
void printResults(char* title, int passedTests, int failedTests)
{ 
    printf("----------------------------------------------------\n");
    printf("        TEST: %s\n", title);
    printf("----------------------------------------------------\n");
    printf(" Tests passed: %d\n", passedTests);
    printf(" Tests failed: %d\n\n", failedTests);
}

int main()
{ 
    // TEST: Smithy card effect
    printf("----------------------------------------------------------------------------------------\n");
    printf("                     RANDOM TESTING: Smithy card effect\n");
    printf("----------------------------------------------------------------------------------------\n\n");

    // Set test variables
    struct testOutcome testVar;
    testVar.passDrawCard = 0;
    testVar.failDrawCard = 0;
    testVar.passDiscardCard = 0;
    testVar.failDiscardCard = 0;

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
  
        // Get random discard count 
        state.discardCount[player] = floor(Random() * MAX_DECK);
      
        // Get random hand count 
        state.handCount[player] = floor(Random() * MAX_HAND);
             
        // Get random played card count 
        state.playedCardCount = floor(Random() * MAX_DECK);

        // Get random hand position and set to smithy card
        handPos = floor(Random() * state.handCount[player]);
        state.hand[player][handPos] = smithy; 

        // Call test function
        testSmithyCard(player, handPos, &state, &testVar);
    }

    printResults("Draw 3 Cards", testVar.passDrawCard, testVar.failDrawCard);
    printResults("Smithy Card Discarded", testVar.passDiscardCard, testVar.failDiscardCard);

    return 0;   
}


int testSmithyCard(int player, int handPos, struct gameState *postState, struct testOutcome *testVar)
{
    // Save game state
    struct gameState preState;
    memcpy(&preState, postState, sizeof(struct gameState));

    // Play smithy card
    cardEffect(smithy, 0, 0, 0, postState, handPos, 0); 

    // Save test conditions
    int preHandCount = preState.handCount[player];
    int preDeckCount = preState.deckCount[player];
    int preDiscardCount = preState.discardCount[player];
    int prePlayedCardCount = preState.playedCardCount; 

    /* Simulate smithy card effects on preState */

    // Draw 3 cards
    // CREDIT: testDrawCard.c
    int i;
    for (i = 0; i < 3; i++)
    { 
        if (preState.deckCount[player] > 0)
        {
            preState.handCount[player]++;
            preState.hand[player][preState.handCount[player]-1] = preState.deck[player][preState.deckCount[player]-1];
            preState.deckCount[player]--;
        }
        else if (preState.discardCount[player] > 0)
        {
            memcpy(preState.deck[player], postState->deck[player], sizeof(int) * preState.discardCount[player]);
            memcpy(preState.discard[player], postState->discard[player], sizeof(int) * preState.discardCount[player]);
            preState.hand[player][postState->handCount[player]-1] = postState->hand[player][postState->handCount[player]-1];
            preState.handCount[player]++;
            preState.deckCount[player] = preState.discardCount[player] - 1;
            preState.discardCount[player] = 0;
        } 
    }
     
    // Discard smithy card  
    preState.playedCards[preState.playedCardCount] = preState.hand[player][handPos];
    preState.playedCardCount++;

    // Set position of smithy card to -1
    int handCount = preState.handCount[player];
    preState.hand[player][handPos] = -1;

    // Card in last position of hand
    if (handPos == (handCount - 1))
        preState.handCount[player]--;

    else
    {     
        preState.hand[player][handPos] = preState.hand[player][handCount - 1];
        preState.hand[player][handCount - 1] = -1;
        preState.handCount[player]--;
    }      

    // Compare pre and post state of game 

    // TEST: 3 cards drawn
    if (preState.handCount[player] == postState->handCount[player] && preState.deckCount[player] == postState->deckCount[player])
    {
        // Print test conditions
        printf("-----------------------------------------------TEST PASSED: 3 Cards Drawn--------------------------------------\n");
        printf("TEST CONDITIONS\n");
        printf("Player: %d   Hand Count: %d   Deck Count: %d   Discard Count: %d   Played Card Count: %d   Hand Position: %d\n", player + 1, preHandCount, preDeckCount, preDiscardCount, prePlayedCardCount, handPos);   
        printf("---------------------------------------------------------------------------------------------------------------\n\n");
        testVar->passDrawCard++;
    }
    else
    {
        testVar->failDrawCard++;
    }
     
    // TEST: Smithy card discarded
    if (preState.playedCardCount == postState->playedCardCount)
    { 
        testVar->passDiscardCard++;
    }
    else
    { 
        // Print test conditions
        printf("-----------------------------------TEST FAILED: Smithy Card Discarded--------------------------\n");
        printf("TEST CONDITIONS\n");
        printf("Player: %d   Hand Count: %d   Deck Count: %d   Discard Count: %d   Played Card Count: %d   Hand Position: %d\n", player + 1, preHandCount, preDeckCount, preDiscardCount, prePlayedCardCount, handPos);   
        printf("----------------------------------------------------------------------------------------------\n\n");

        testVar->failDiscardCard++;
    }
          
    return 0;
}






