/***************************************************************************
** Filename: cardtest4.c
** Author: William Ryan Brooks
** Date: 2018-02-04
** Description: Unit test for the outpost card effect in dominion.c
****************************************************************************/
#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"
#include <stdlib.h>

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
    // TEST: Outpost card effect
    printf("---------------------------------------------------------\n");
    printf("              TESTING: Outpost card effect\n");
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

    // Add outpost card to hand
    state.hand[player][0] = outpost;
 
    memcpy(&testState, &state, sizeof(struct gameState));
 
    cardEffect(outpost, 0, 0, 0, &testState, 0, 0);

    // TEST: Outpost flag set
    printf("---------------------------------------------------\n");
    printf("    TEST: Outpost flag set\n");    
    printf("---------------------------------------------------\n");

    printf("testState.outpostPlayed = %d, expected = %d\n", testState.outpostPlayed, state.outpostPlayed + 1); 
    if (testState.outpostPlayed == state.outpostPlayed + 1)
        assertTest(1, &passedTests);
    else
        assertTest(0, &failedTests); 

    // TEST: Card discarded
    printf("---------------------------------------------------\n");
    printf("    TEST: Card discarded\n");
    printf("---------------------------------------------------\n");
 
    int handCount, numCardPre = 0;
    int maxHandCount = state.handCount[player]; 
    for (handCount = 0; handCount < maxHandCount; handCount++)
    { 
        if (state.hand[player][handCount] == outpost) 
            numCardPre++;
    }
       
    int numCardPost = 0; 
    maxHandCount = testState.handCount[player];
    for (handCount = 0; handCount < maxHandCount; handCount++)
    {
        if (testState.hand[player][handCount] == outpost) 
            numCardPost++;
    } 

    printf("Number of cards = %d, expected = %d\n", numCardPost, numCardPre - 1);
    if (numCardPost == numCardPre - 1)
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
}

     

    
    


    
