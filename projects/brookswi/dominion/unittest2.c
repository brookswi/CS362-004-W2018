/***************************************************************************
** Filename: unittest2.c
** Author: William Ryan Brooks
** Date: 2018-02-04
** Description: Unit test for the isGameOver() function in dominion.c
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
    // TEST: isGameOver() function:
    printf("---------------------------------------------------------\n");
    printf("              TESTING: isGameOver() function\n");
    printf("---------------------------------------------------------\n\n");

    int passedTests = 0;
    int failedTests = 0;

    struct gameState state;

    int k[10] = {adventurer, council_room, feast, gardens, mine, remodel, smithy, village, baron, great_hall};
 
    // Game with max players 
    int retValue = initializeGame(MAX_PLAYERS, k, 1, &state);

    // Check that game is valid
    assert(retValue == 0);    
    
    // TEST: New game, so game is not over
    printf("---------------------------------------------------\n");
    printf("    TEST: New game started, so game is not over\n");
    printf("---------------------------------------------------\n");
 
    printf("isGameOver(&state) = %d, expected = 0\n", isGameOver(&state));
    if (isGameOver(&state) == 0)
        assertTest(1, &passedTests);
    else
        assertTest(0, &failedTests);

    // Test: Stack of province cards is not empty, so game is not over
    printf("------------------------------------------------------------------------\n"); 
    printf("    TEST: Stack of province cards is not empty, so game is not over\n");
    printf("------------------------------------------------------------------------\n");
    
    printf("isGameOver(&state) = %d, expected = 0\n", isGameOver(&state));
    state.supplyCount[province] = 1;
    if (isGameOver(&state) == 0)
        assertTest(1, &passedTests);
    else
        assertTest(0, &failedTests);

    // Test: Stack of province cards is empty, so game is over
    printf("--------------------------------------------------------------\n"); 
    printf("    TEST: Stack of province cards is empty, so game is over\n");
    printf("--------------------------------------------------------------\n");
   
    printf("isGameOver(&state) = %d, expected = 1\n", isGameOver(&state));
    state.supplyCount[province] = 0;
    if (isGameOver(&state) == 1)
        assertTest(1, &passedTests);
    else
        assertTest(0, &failedTests);

    // Test: There are not three or more empty supply piles, so game is not over
    printf("----------------------------------------------------------------------------------\n");  
    printf("    TEST: There are not three or more empty supply piles, so game is not over\n");
    printf("----------------------------------------------------------------------------------\n");
    
    int i;
    for (i = curse; i <= treasure_map; i++) 
        state.supplyCount[i] = 1;  
    printf("isGameOver(&state) = %d, expected = 0\n", isGameOver(&state));
    if (isGameOver(&state) == 0)
        assertTest(1, &passedTests);
    else
        assertTest(0, &failedTests);

    // Test: There are three empty supply piles, so game is over
    printf("----------------------------------------------------------------------\n");   
    printf("    TEST: There are three empty supply piles, so game is over\n"); 
    printf("----------------------------------------------------------------------\n");

    // Set all cards to be non-empty
    for (i = curse; i <= treasure_map; i++)
        state.supplyCount[i] = 1;  

    char* cardNames[27] = {"curse", "estate", "duchy", "province", "copper", "silver", "gold", "adventurer", "council room", "feast", "gardens", "mine", "remodel", "smithy", "village", "baron", "great hall", "minion", "steward", "tribute", "ambassador", "cutpurse", "embargo", "outpost", "salvager", "sea hag", "treasure map"}; 
    
    // Loop through all cards, setting three cards to empty and checking if game is over 
    for (i = curse; i <= treasure_map - 2; i++) 
    {
        // Set previous value back to 1
        if (i != 0) 
            state.supplyCount[i - 1] = 1; 

        // Set three cards to 0
        state.supplyCount[i] = 0;
        state.supplyCount[i + 1] = 0;   
        state.supplyCount[i + 2] = 0;

        printf("Empty supply piles: %s, %s, %s\n", cardNames[i], cardNames[i + 1], cardNames[i + 2]); 
        printf("isGameOver(&state) = %d, expected = 1\n", isGameOver(&state)); 
        if (isGameOver(&state) == 1)
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

     

    
    


    
