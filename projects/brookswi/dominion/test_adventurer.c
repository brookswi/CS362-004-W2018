// Unit test for adventurer card

/*
 * Include the following lines in your makefile:
 *
 * test_adventurer: test_adventurer.c dominion.o rngs.o
 *      gcc -o test_adventurer -g  test_adventurer.c dominion.o rngs.o $(CFLAGS)
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
 
    int player = 0;
    int gainCards = 2;
    int discardCards = 1;
  
    memcpy(&testState, &state, sizeof(struct gameState));
 
    cardEffect(adventurer, 0, 0, 0, &testState, 0, 0);

    // TEST: 2 cards added to hand and adventurer card discarded
    printf("TEST: 2 cards added to hand and adventurer card discarded\n");
    if (testState.handCount[player] == state.handCount[player] + gainCards - discardCards)
        assertTest(1);
    else
        assertTest(0); 
     
    // TEST: 2 more treasure cards are in hand than before
    printf("TEST: 2 more treasure cards are in hand than before\n");
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
 
    if (postHand == preHand + 2)
        assertTest(1);
    else
        assertTest(0); 

    // TEST: All of the non-treasure cards that were drawn have been discarded
    printf("TEST: All of the non-treasure cards that were drawn have been discarded\n");
    int sameCards; 
    maxHandCount = state.handCount[player]; 
    for (handCount = 0; handCount < maxHandCount; handCount++)
    {
        if (testState.hand[player][handCount] == state.hand[player][handCount])
            sameCards = 1;
        else
            sameCards = 0;
    }
        
    if (sameCards == 1)
        assertTest(1);
    else
        assertTest(0);  

}

     

    
    


    
