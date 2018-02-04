// Unit test for getCost function

/*
 * Include the following lines in your makefile:
 *
 * test_getCost: test_getCost.c dominion.o rngs.o
 *      gcc -o test_getCost -g  test_getCost.c dominion.o rngs.o $(CFLAGS)
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
    // Create variables for costs of all cards
    // All costs verified from wiki.dominionstrategy.com
    int cardCosts[] = {0, 2, 5, 8, 0, 3, 6, 6, 5, 4, 4, 5, 4, 4, 3, 4, 3, 5, 3, 5, 3, 4, 2, 5, 4, 4, 4};

    int card;
    for (card = curse; card <= treasure_map; card++)
    {
        if (getCost(card) == cardCosts[card])
            assertTest(1);
        else
            assertTest(0); 
    }
 
    return 0;
}

     

    
    


    
