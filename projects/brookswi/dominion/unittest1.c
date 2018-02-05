/***************************************************************************
** Filename: unittest1.c
** Author: William Ryan Brooks
** Date: 2018-02-04
** Description: Unit test for the getCost() function in dominion.c
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
    // TEST: getCost() function:
    printf("---------------------------------------------------------\n");
    printf("               TESTING: getCost() function\n");
    printf("---------------------------------------------------------\n\n");

    int passedTests = 0;
    int failedTests = 0;
    
    // Create variables for costs of all cards
    // All costs verified from wiki.dominionstrategy.com
    char* cardNames[27] = {"curse", "estate", "duchy", "province", "copper", "silver", "gold", "adventurer", "council room", "feast", "gardens", "mine", "remodel", "smithy", "village", "baron", "great hall", "minion", "steward", "tribute", "ambassador", "cutpurse", "embargo", "outpost", "salvager", "sea hag", "treasure map"};
    int cardCosts[] = {0, 2, 5, 8, 0, 3, 6, 6, 5, 4, 4, 5, 4, 4, 3, 4, 3, 5, 3, 5, 3, 4, 2, 5, 4, 4, 4};
     
    int card;
    for (card = curse; card <= treasure_map; card++)
    {
        printf("---------------------------------------------------\n");
        printf("          TEST: Cost of %s card\n", cardNames[card]);
        printf("---------------------------------------------------\n");

        printf("getCost(card) = %d, expected = %d\n", getCost(card), cardCosts[card]);
        if (getCost(card) == cardCosts[card])
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

     

    
    


    
