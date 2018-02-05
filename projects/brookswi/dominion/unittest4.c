/***************************************************************************
** Filename: unittest4.c
** Author: William Ryan Brooks
** Date: 2018-02-04
** Description: Unit test for the whoseTurn() function in dominion.c
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
    { 
        printf("--------TEST PASSED--------\n\n");
    }
    else
        printf("--------TEST FAILED--------\n\n");
    (*tests)++;
}


int main()
{
    // TEST: whoseTurn() function:
    printf("---------------------------------------------------------\n");
    printf("              TESTING: whoseTurn() function\n");
    printf("---------------------------------------------------------\n\n");

    int passedTests = 0; 
    int failedTests = 0;

    struct gameState state;

    int k[10] = {adventurer, council_room, feast, gardens, mine, remodel, smithy, village, baron, great_hall};
 
    // Game with max players  
    int retValue = initializeGame(MAX_PLAYERS, k, 1, &state);

    // Check that game is valid
    assert(retValue == 0);    
    
    // Test: Game starts with player 1's turn
    printf("---------------------------------------------------\n");
    printf("    TEST: Game starts with player 1's turn\n");
    printf("---------------------------------------------------\n");

    printf("whoseTurn(&state) = %d, expected = 0\n", whoseTurn(&state)); 
    if (whoseTurn(&state) == 0)
        assertTest(1, &passedTests);
    else
        assertTest(0, &failedTests);

    // Test: Check for each player's turn
    int i;
    for (i = 0; i < MAX_PLAYERS; i++)
    {
        printf("---------------------------------------------------\n");
        printf("    TEST: Player %d's turn\n", i + 1);  
        printf("---------------------------------------------------\n");
  
        state.whoseTurn = i;
        printf("whoseTurn(&state) = %d, expected = %d\n", whoseTurn(&state), i); 
        if (whoseTurn(&state) == i)
            assertTest(1, &passedTests);
        else
            assertTest(0, &failedTests);
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

     

    
    


    
