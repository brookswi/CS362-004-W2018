// Unit test for smithy card

/*
 * Include the following lines in your makefile:
 *
 * test_smithy: test_smithy.c dominion.o rngs.o
 *      gcc -o test_smithy -g  test_smithy.c dominion.o rngs.o $(CFLAGS)
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

    // TEST: Draw 3 cards
    int player = 0;
    int gainCards = 3;
    int discardCards = 1;

    memcpy(&testState, &state, sizeof(struct gameState));
 
    cardEffect(smithy, 0, 0, 0, &testState, 0, 0);

    if (testState.handCount[player] == state.handCount[player] + gainCards - discardCards)
        assertTest(1);
    else
        assertTest(0); 
     
    return 0;
}

     

    
    


    
