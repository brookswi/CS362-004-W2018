// Unit test for whoseTurn function


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
        printf(GREEN "---TEST PASSED---\n\n" RESET);
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
    
    // Test: Game starts with player 1's turn
    printf("TEST: Game starts with player 1's turn\n");
    if (whoseTurn(&state) == 0)
        assertTest(1);
    else
        assertTest(0);

    // Test: Check for each player's turn
    int i;
    for (i = 0; i < MAX_PLAYERS; i++)
    {
        printf("TEST: Player %d's turn\n", i + 1); 
        state.whoseTurn = i;
        if (whoseTurn(&state) == i)
            assertTest(1);
        else
            assertTest(0);
    }
 
    return 0;
}

     

    
    


    
