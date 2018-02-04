// Unit test for isGameOver function

/*
 * Include the following lines in your makefile:
 *
 * test_isGameOver: test_isGameOver.c dominion.o rngs.o
 *      gcc -o test_isGameOver -g  test_isGameOver.c dominion.o rngs.o $(CFLAGS)
 */

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
    {
        return;
        //printf(GREEN "---TEST PASSED---\n\n" RESET);
    }
    else
        printf(RED "---TEST FAILED---\n\n" RESET);
}

int main()
{
    struct gameState state;

    int k[10] = {adventurer, council_room, feast, gardens, mine, remodel, smithy, village, baron, great_hall};
 
    // Game with max players 
    printf("Testing for game with 4 players\n\n");
    int retValue = initializeGame(4, k, 1, &state);

    // Check that game is valid
    assert(retValue == 0);    
    
    // Test: New game, so game is not over
    printf("Test: New game started, so game is not over\n");
    if (isGameOver(&state) == 0)
        assertTest(1);
    else
        assertTest(0);

    // Test: Stack of province cards is not empty, so game is not over
    printf("Test: Stack of province cards is not empty, so game is not over\n");
    state.supplyCount[province] = 1;
    if (isGameOver(&state) == 0)
        assertTest(1);
    else
        assertTest(0);

    // Test: Stack of province cards is empty, so game is over
    printf("Test: Stack of province cards is empty, so game is over\n");
    state.supplyCount[province] = 0;
    if (isGameOver(&state) == 1)
        assertTest(1);
    else
        assertTest(0);

    // Test: There are not three or more empty supply piles, so game is not over
    printf("Test: There are not three or more empty supply piles, so game is not over\n");
    int i;
    for (i = curse; i <= treasure_map; i++)
        state.supplyCount[i] = 1; 
    if (isGameOver(&state) == 0)
        assertTest(1);
    else
        assertTest(0);

    // Test: There are three empty supply piles, so game is over
    printf("Test: There are three empty supply piles, so game is over\n"); 

    // Set all cards to be non-empty
    for (i = curse; i <= treasure_map; i++)
        state.supplyCount[i] = 1;  

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
              
        if (isGameOver(&state) == 1)
            assertTest(1);
        else
            assertTest(0);
    }
 
    return 0;
}

     

    
    


    
