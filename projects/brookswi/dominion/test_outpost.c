// Unit test for outpost card

#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"
#include <stdlib.h>

// https://stackoverflow.com/questions/3585846/color-text-in-terminal-applications-in-unix
#define RED "\x1B[31m"
#define GREEN "\x1B[32m"
#define YELLOW "\x1B[33m"
#define RESET "\033[0m"


void assertTest(int val)
{
    if (val == 1)
        printf(GREEN "---TEST PASSED---\n\n" RESET);
    else
        printf(RED "---TEST FAILED---\n\n" RESET);
}

int main()
{ 
    struct gameState state, testState;

    int k[10] = {adventurer, council_room, feast, gardens, mine, remodel, smithy, village, baron, great_hall};
 
    // Game with max players 
    printf("Testing for game with 4 players\n\n");
    int retValue = initializeGame(4, k, 1, &state);

    // Check that game is valid
    assert(retValue == 0); 

    int player = 0;

    // Add outpost card to hand
    state.hand[player][0] = outpost;
 
    memcpy(&testState, &state, sizeof(struct gameState));
 
    cardEffect(outpost, 0, 0, 0, &testState, 0, 0);

    // TEST: Outpost flag set
    printf("TEST: Outpost flag set\n");
    if (testState.outpostPlayed == state.outpostPlayed + 1)
        assertTest(1);
    else
        assertTest(0); 

    // TEST: Card discarded
    printf("TEST: Card discarded\n");
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

    if (numCardPost == numCardPre - 1)
        assertTest(1);
    else
        assertTest(0);
 
    return 0;
}

     

    
    


    
