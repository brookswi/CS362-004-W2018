// Unit test for salvager card

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
 
    int player = 0; 

    int card;
    for (card = curse; card <= treasure_map; card++)
    {
        // Clear game states
        memset(&testState, 23, sizeof(struct gameState));
        memset(&state, 23, sizeof(struct gameState));
        int retValue = initializeGame(4, k, 1, &state);

        // Check that game is valid
        assert(retValue == 0); 

        // Add card to hand
        state.hand[player][2] = card;   

        // Add salvager card to hand 
        state.hand[player][1] = salvager;
  
        memcpy(&testState, &state, sizeof(struct gameState));
  
        cardEffect(salvager, 2, 0, 0, &testState, 1, 0);

        // TEST: Number of buys increased by 1
        printf("TEST: Number of buys increased by 1\n");
        if (testState.numBuys == state.numBuys + 1)
            assertTest(1);
        else
            assertTest(0); 

        // TEST: Gained coins equal to trashed card
        printf("TEST: Gained coins equal to trashed card\n");
        int cardValue = getCost(card);
        printf("testState.coins: %d state.coins + cardValue: %d state.coins: %d cardValue: %d\n", testState.coins, state.coins + getCost(card), state.coins, cardValue);
        if (testState.coins == state.coins + cardValue)
            assertTest(1);
        else
            assertTest(0);
                
        // TEST: Card trashed
        printf("TEST: Card trashed\n");
        int handCount, numCardPre = 0;
        int maxHandCount = state.handCount[player]; 
        for (handCount = 0; handCount < maxHandCount; handCount++)
        { 
            if (state.hand[player][handCount] == card) 
                numCardPre++;
        }
       
        int numCardPost = 0; 
        maxHandCount = testState.handCount[player];
        for (handCount = 0; handCount < maxHandCount; handCount++)
        {
            if (testState.hand[player][handCount] == card) 
                numCardPost++;
        } 

        if (numCardPost == numCardPre - 1)
            assertTest(1);
        else
            assertTest(0);
    } 
 
    return 0;
}

     

    
    


    
