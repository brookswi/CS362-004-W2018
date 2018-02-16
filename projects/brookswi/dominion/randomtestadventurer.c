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
#include <assert.h>
#include <time.h>
#include "rngs.h"
#include <stdlib.h>

// Function prototype
int testAdventurerCard(int drawntreasure, int player, struct gameState *state, int temphand[], int z, int testCase)


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
    // Initialize RNG
    time_t t;
    srand((unsigned) time(&t));   

    int num, player, i;

    int temphand[MAX_HAND];     // temphand always passed as empty array
    int drawntreasure = 0;      // drawntreasure always passed as 0
    int z = 0;                  // z always passed as 0

    int k[10] = {adventurer, council_room, feast, gardens, mine, remodel, smithy, village, baron, great_hall};

    struct gameState state;

    for (num = 0; num < 2000; num++)
    {
        for (i = 0; i < sizeof(struct gameState); i++)
        {
            ((char*) &state)[i] = rand() % 256;
        }
        player = rand() % 4;

        // Case 1: Deck empty, shuffle necessary
        state.deckCount[player] = 0;
        state.discardCount[player] = rand() % MAX_DECK;
        state.handCount[player] = rand() % MAX_HAND; 
        testAdventurerCard(drawntreasure, player, &state, temphand, z, 1);

        /*
        state.deckCount[player] = rand() % MAX_DECK;
        state.discardCount[player] = rand() % MAX_DECK;
        state.handCount[player] = rand() % MAX_HAND; 
        testAdventurerCard(drawntreasure, player, &state, temphand, z);
        */

    }

    return 0;   
}



int testAdventurerCard(int drawntreasure, int player, struct gameState *postState, int temphand[], int z, int testCase)
{
    struct gameState preState;
    memcpy(&preState, postState, sizeof(struct gameState));    

    int advResult;
    advResult = adventurerEffect(drawntreasure, player, postState, temphand, z); 
   
    // Discard adventurer card
    preState.handCount[player]--;

    // Gain two treasure cards in hand
    preState.handCount[player]++;

 
    /*
    if (preState.discardCount[player] > 0)
    {
        memcpy(preState.deck[player], postState->deck[player], sizeof(int) * preState.discardCount[player]);
        memcpy(preState.discard[player], postState->discard[player], sizeof(int) * preState.discardCount[player]);
        preState.hand[player][postState->handCount[player]-1] = postState->hand[player][postState->handCount[player]-1];
    }
    */

       






    /*
    // TEST: Adventurer card effect
    printf("---------------------------------------------------------\n");
    printf("              TESTING: Adventurer card effect\n");
    printf("---------------------------------------------------------\n\n");

    int passedTests = 0;
    int failedTests = 0;

    struct gameState state, testState;

    int k[10] = {adventurer, council_room, feast, gardens, mine, remodel, smithy, village, baron, great_hall};
 
    // Game with max players  
    int retValue = initializeGame(MAX_PLAYERS, k, 1, &state);

    // Check that game is valid
    assert(retValue == 0); 
 
    int player = 0;
    int gainCards = 2;
    int discardCards = 1;
  
    memcpy(&testState, &state, sizeof(struct gameState));
 
    cardEffect(adventurer, 0, 0, 0, &testState, 0, 0);

    // TEST: 2 cards added to hand and adventurer card discarded
    printf("---------------------------------------------------------------\n");
    printf("    TEST: 2 cards added to hand and adventurer card discarded\n"); 
    printf("---------------------------------------------------------------\n");

    printf("testState.handCount[player] = %d, expected = %d\n", testState.handCount[player], state.handCount[player] + gainCards - discardCards); 
    if (testState.handCount[player] == state.handCount[player] + gainCards - discardCards)
        assertTest(1, &passedTests);
    else
        assertTest(0, &failedTests); 
     
    // TEST: 2 more treasure cards are in hand than before
    printf("-------------------------------------------------------------------\n");
    printf("    TEST: Exactly 2 more treasure cards are in hand than before\n");
    printf("-------------------------------------------------------------------\n");
 
    int handCount, preHand, postHand;
    int maxHandCount = state.handCount[player];
    for (handCount = 0; handCount < maxHandCount; handCount++)
    {
        if (state.hand[player][handCount] == copper || state.hand[player][handCount] == silver || state.hand[player][handCount] == gold)    preHand++;
    }
  
    maxHandCount = testState.handCount[player]; 
    for (handCount = 0; handCount < maxHandCount; handCount++)
    {
        if (testState.hand[player][handCount] == copper || testState.hand[player][handCount] == silver || testState.hand[player][handCount] == gold)    postHand++;
    }
 
    printf("Number of treasure cards in hand = %d, expected = %d\n", postHand, preHand + 2);
    if (postHand == preHand + 2)
        assertTest(1, &passedTests);
    else
        assertTest(0, &failedTests); 

    // TEST: All of the non-treasure cards that were drawn have been discarded
    printf("---------------------------------------------------------------------------------\n");
    printf("    TEST: All of the non-treasure cards that were drawn have been discarded\n"); 
    printf("---------------------------------------------------------------------------------\n");
 
    int sameCards; 
    maxHandCount = state.handCount[player]; 
    for (handCount = 0; handCount < maxHandCount; handCount++)
    {
        if (testState.hand[player][handCount] == state.hand[player][handCount])
            sameCards = 1;
        else
            sameCards = 0;
    }
        
    printf("Same cards as before = %d, expected = 1\n", sameCards);
    if (sameCards == 1)
        assertTest(1, &passedTests);
    else
        assertTest(0, &failedTests);  

    printf("\n");
    printf("-----------------------------------------------------\n");
    printf("         Tests passed: %d\n", passedTests);
    printf("-----------------------------------------------------\n");

    printf("\n");
    printf("-----------------------------------------------------\n");
    printf("         Tests failed: %d\n", failedTests);
    printf("-----------------------------------------------------\n");

    return 0;
    */
}

     

    
    


    
