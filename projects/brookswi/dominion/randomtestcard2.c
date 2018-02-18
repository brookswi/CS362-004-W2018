/***************************************************************************
** Filename: randomtestcard2.c
** Author: William Ryan Brooks
** Date: 2018-02-18
** Description: Random test for the outpost card effect in dominion.c
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
int testOutpostCard(int player, int handPos, struct gameState *state, int* passedTests, int* failedTests);

void assertTest(int val, int *tests)
{
    if (val == 1)
    {
        // Suppress output
        ;
        //printf("--------TEST PASSED--------\n\n");
    }
    else
        printf("--------TEST FAILED--------\n\n");
    (*tests)++;
}

int main()
{ 
    // TEST: Outpost card effect
    printf("----------------------------------------------------------------------------\n");
    printf("                RANDOM TESTING: Outpost card effect\n");
    printf("----------------------------------------------------------------------------\n\n");


    // Keep track of tests
    int passedTests = 0;
    int failedTests = 0;

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
        
        // Set outpost flag to 0
        state.outpostPlayed = 0;

        // Get random hand position and set to outpost card 
        handPos = floor(Random() * state.handCount[player]);
        state.hand[player][handPos] = outpost; 

        // Call test function
        testOutpostCard(player, handPos, &state, &passedTests, &failedTests); 
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


int testOutpostCard(int player, int handPos, struct gameState *postState, int* passedTests, int* failedTests)
{
    // Save game state
    struct gameState preState;
    memcpy(&preState, postState, sizeof(struct gameState));

    // Play outpost card
    cardEffect(outpost, 0, 0, 0, postState, handPos, 0);

    // Save preState variables
    int preHandCount = preState.handCount[player];
    int preDeckCount = preState.deckCount[player];
    int preDiscardCount = preState.discardCount[player];

    /* Simulate outpost card effects on preState */

    // Set outpost flag
    preState.outpostPlayed++;
     
    // Discard outpost card   
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
    { 
        assertTest(0, failedTests); 

        // Print test conditions 
        printf("TEST CONDITIONS\n");
        printf("Player: %d   Hand Count: %d   Deck Count: %d   Discard Count: %d   Hand Position: %d\n", player + 1, preHandCount, preDeckCount, preDiscardCount, handPos);
    }
          
    return 0;
}






