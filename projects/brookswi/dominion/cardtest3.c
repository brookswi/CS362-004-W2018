/***************************************************************************
** Filename: cardtest3.c
** Author: William Ryan Brooks
** Date: 2018-02-04
** Description: Unit test for the salvager card effect in dominion.c
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
    // TEST: Salvager card effect
    printf("---------------------------------------------------------\n");
    printf("              TESTING: Salvager card effect\n");
    printf("---------------------------------------------------------\n\n");

    int passedTests = 0;
    int failedTests = 0;

    struct gameState state, testState;

    int k[10] = {adventurer, council_room, feast, gardens, mine, remodel, smithy, village, baron, great_hall};
  
    int player = 0; 

    char* cardNames[27] = {"curse", "estate", "duchy", "province", "copper", "silver", "gold", "adventurer", "council room", "feast", "gardens", "mine", "remodel", "smithy", "village", "baron", "great hall", "minion", "steward", "tribute", "ambassador", "cutpurse", "embargo", "outpost", "salvager", "sea hag", "treasure map"}; 

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
        printf("-----------------------------------------------------------\n");
        printf("    TEST: Number of buys increased by 1\n"); 
        printf("-----------------------------------------------------------\n");

        printf("Trashed card: %s\n", cardNames[card]);
        printf("testState.numBuys = %d, expected = %d\n", testState.numBuys, state.numBuys + 1); 
        if (testState.numBuys == state.numBuys + 1)
            assertTest(1, &passedTests);
        else
            assertTest(0, &failedTests); 

        // TEST: Gained coins equal to trashed card
        printf("-----------------------------------------------------------\n");
        printf("    TEST: Gained coins equal to trashed card\n"); 
        printf("-----------------------------------------------------------\n");
 
        int cardValue = getCost(card);
        printf("Trashed card: %s\n", cardNames[card]);
        printf("testState.coins: %d, expected = %d\n", testState.coins, state.coins + cardValue);
        if (testState.coins == state.coins + cardValue)
            assertTest(1, &passedTests);
        else
            assertTest(0, &failedTests);
                
        // TEST: Card trashed
        printf("-------------------------------------------------\n");
        printf("    TEST: Card trashed\n"); 
        printf("-------------------------------------------------\n");
 
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

        printf("Trashed card: %s\n", cardNames[card]);
        printf("Number of cards = %d, expected = %d\n", numCardPost, numCardPre - 1);
        if (numCardPost == numCardPre - 1)
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

     

    
    


    
