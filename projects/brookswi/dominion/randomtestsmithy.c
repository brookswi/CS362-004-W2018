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

// Function prototype
int testSmithyCard(int player, int handPos, struct gameState *state, int* passedTests, int* failedTests);

void assertTest(int val, int *tests)
{
    if (val == 1)
        printf("--------TEST PASSED--------\n\n");
    else
        printf("--------TEST FAILED--------\n\n");
    (*tests)++;
}

int main()
{ 
    // Keep track of tests
    int passedTests = 0;
    int failedTests = 0;

    // Initialize RNG
    //time_t t;
    //srand((unsigned) time(&t));   
    SelectStream(2);
    PutSeed(3);

    int num, player, handPos, i;

    // Create game state
    struct gameState state;

    // Number of tests
    for (num = 0; num < 1000; num++)
    {
        for (i = 0; i < sizeof(struct gameState); i++)
            ((char*)&state)[i] = floor(Random() * 256);

        // Get random player
        state.numPlayers = MAX_PLAYERS;
        //player = rand() % 4; 
        player = floor(Random() * 4);
        state.whoseTurn = player;
      
        // Fill deck with random cards
        //state.deckCount[player] = rand() % MAX_DECK;
        state.deckCount[player] = floor(Random() * MAX_DECK);
        /*
        int deckCount = state.deckCount[player];
        for (i = 0; i < deckCount; i++)
            state.deck[player][i] = rand() % treasure_map;
        */

        // Fill discard with random cards
        //state.discardCount[player] = rand() % MAX_DECK; 
        state.discardCount[player] = floor(Random() * MAX_DECK);
        /*
        int discardCount = state.discardCount[player];
        for (i = 0; i < discardCount; i++)
            state.discard[player][i] = rand() % treasure_map;
        */

        // Fill hand with random cards
        //state.handCount[player] = rand() % MAX_HAND; 
        state.handCount[player] = floor(Random() * MAX_HAND);
        /*
        int handCount = state.handCount[player];
        for (i = 0; i < handCount; i++)
            state.hand[player][i] = rand() % treasure_map;
        */
        
        // Fill played cards with random cards
        //state.playedCardCount = rand() % MAX_DECK;
        state.playedCardCount = floor(Random() * MAX_DECK);
        /*
        int playedCardCount = state.playedCardCount;
        for (i = 0; i < playedCardCount; i++)
            state.playedCards[i] = rand() % treasure_map;
        */

        // Set outpost flag to 0
        state.outpostPlayed = 0;

        // Get random hand position and set to outpost card
        //handPos = rand() % state.handCount[player];
        handPos = floor(Random() * state.handCount[player]);
        state.hand[player][handPos] = outpost; 

        // Call test function
        testSmithyCard(player, handPos, &state, &passedTests, &failedTests); 
    }

    printf("\n"); 
    printf("-----------------------------------------------------\n");
    printf("         Tests passed: %d\n", passedTests);
    printf("-----------------------------------------------------\n");

    printf("\n");
    printf("-----------------------------------------------------\n");
    printf("         Tests failed: %d\n", failedTests);
    printf("-----------------------------------------------------\n");

    return 0;   
}


int testSmithyCard(int player, int handPos, struct gameState *postState, int* passedTests, int* failedTests)
{
    // Save game state
    struct gameState preState;
    memcpy(&preState, postState, sizeof(struct gameState));

    // Play smithy card
    cardEffect(smithy, 0, 0, 0, postState, handPos, 0); 

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

    // Set position of outpost card to -1
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
    if (memcmp(&preState, postState, sizeof(struct gameState)) == 0)     
        assertTest(1, passedTests);  
    else 
        assertTest(0, failedTests); 
  
    /*
    if (preState.outpostPlayed == postState->outpostPlayed)
        assertTest(1, passedTests);
    else
        assertTest(0, failedTests);
    */
   /* 
    if (preState.handCount[player] == postState->handCount[player])
        assertTest(1, passedTests);
    else
        assertTest(0, failedTests);
    */
        
    return 0;
}






