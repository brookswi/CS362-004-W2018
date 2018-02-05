/***************************************************************************
** Filename: unittest3.c
** Author: William Ryan Brooks
** Date: 2018-02-04
** Description: Unit test for the fullDeckCount() function in dominion.c
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

// Function to set all cards in the player's hand, deck, and discard to a single card
void clearCards(int player, int card, struct gameState *state)
{
    // Set all cards to a single card for uniformity
    if (card == curse || card == treasure_map)
    {
        int i; 
        int adventurers[MAX_HAND];
        for (i = 0; i < MAX_HAND; i++)
            adventurers[i] = adventurer;

        memcpy(state->hand[player], adventurers, sizeof(int) * MAX_HAND);
        memcpy(state->deck[player], adventurers, sizeof(int) * MAX_DECK);
        memcpy(state->discard[player], adventurers, sizeof(int) * MAX_DECK); 
    }    
    else
    {
        int i; 
        int cards[MAX_HAND];
        for (i = 0; i < MAX_HAND; i++)
            cards[i] = card + 1;

        memcpy(state->hand[player], cards, sizeof(int) * MAX_HAND);
        memcpy(state->deck[player], cards, sizeof(int) * MAX_DECK);
        memcpy(state->discard[player], cards, sizeof(int) * MAX_DECK);
    }
}


int main()
{
    // TEST: fullDeckCount() function:
    printf("---------------------------------------------------------\n");
    printf("              TESTING: fullDeckCount() function\n");
    printf("---------------------------------------------------------\n\n");

    int passedTests = 0; 
    int failedTests = 0;

    struct gameState state;

    int k[10] = {adventurer, council_room, feast, gardens, mine, remodel, smithy, village, baron, great_hall};

    char* cardNames[27] = {"curse", "estate", "duchy", "province", "copper", "silver", "gold", "adventurer", "council room", "feast", "gardens", "mine", "remodel", "smithy", "village", "baron", "great hall", "minion", "steward", "tribute", "ambassador", "cutpurse", "embargo", "outpost", "salvager", "sea hag", "treasure map"}; 
 
    // Game with 2 players 
    int retValue = initializeGame(2, k, 1, &state);

    // Check that game is valid
    assert(retValue == 0);    

    int player, card, handCount, deckCount, discardCount; 
    int maxHandCount = 5;
    int maxDeckCount = 10;
    int maxDiscardCount = 10;
    for (player = 0; player < 1; player++)
    { 
        for (card = curse; card <= treasure_map; card++)
        {
            // Set all cards to a single card for uniformity
            clearCards(player, card, &state);           

            // TEST: None of current card in player's full deck
            printf("---------------------------------------------------\n");
            printf("    TEST: None of current card in full deck\n"); 
            printf("---------------------------------------------------\n");

            state.handCount[player] = maxHandCount;
            state.deckCount[player] = maxDeckCount;
            state.discardCount[player] = maxDiscardCount;

            printf("Current card: %s\n", cardNames[card]);
            printf("fullDeckCount(player, card, &state) = %d, expected = 0\n", fullDeckCount(player, card, &state));
            if (fullDeckCount(player, card, &state) == 0)
                assertTest(1, &passedTests);
            else
                assertTest(0, &failedTests); 
    
            // TEST: Card in player's hand, but not in deck or discard
            printf("-----------------------------------------------------------\n"); 
            printf("    TEST: Card in player's hand, but not in deck or discard\n");
            printf("-----------------------------------------------------------\n"); 

            int i; 
            int allPass = 1;
            int handCards[MAX_HAND];
            for (i = 0; i < MAX_HAND; i++)
                handCards[i] = card;
    
            for (handCount = 1; handCount <= maxHandCount; handCount++)
            {
                memcpy(state.hand[player], handCards, sizeof(int) * handCount);  
        
                if (fullDeckCount(player, card, &state) == handCount)
                    allPass = 1; 
                else   
                {
                    allPass = 0;  
                    break;
                }
            }
            if (allPass)
                assertTest(1, &passedTests);
            else
                assertTest(0, &failedTests);
            clearCards(player, card, &state); 

            // TEST: Card in player's deck, but not in hand or discard
            printf("-------------------------------------------------------------------\n");  
            printf("    TEST: Card in player's deck, but not in hand or discard\n");
            printf("-------------------------------------------------------------------\n"); 

            int cards[MAX_DECK];
            for (i = 0; i < MAX_DECK; i++)
                cards[i] = card;
     
            for (deckCount = 1; deckCount <= maxDeckCount; deckCount++)
            {
                memcpy(state.deck[player], cards, sizeof(int) * deckCount);  

                if (fullDeckCount(player, card, &state) == deckCount)
                    allPass = 1; 
                else
                {
                    allPass = 0; 
                    break;
                }
            }
            if (allPass)
                assertTest(1, &passedTests);
            else
                assertTest(0, &failedTests);
            clearCards(player, card, &state);

            // TEST: Card in player's discard, but not in hand or deck
            printf("-------------------------------------------------------------------------\n");   
            printf("    TEST: Card in player's discard, but not in hand or deck\n");
            printf("-------------------------------------------------------------------------\n"); 
             
            for (discardCount = 1; discardCount <= maxDiscardCount; discardCount++)
            {
                memcpy(state.discard[player], cards, sizeof(int) * discardCount);   

                if (fullDeckCount(player, card, &state) == discardCount)
                    allPass = 1; 
                else
                {
                    allPass = 0;
                    break;
                } 
            }
            if (allPass)
                assertTest(1, &passedTests);
            else
                assertTest(0, &failedTests);
            clearCards(player, card, &state);     

            // TEST: Card in player's hand and deck, but not in discard 
          
            printf("-----------------------------------------------------------------------\n");   
            printf("    TEST: Card in player's hand and deck, but not in discard\n"); 
            printf("-----------------------------------------------------------------------\n"); 
 
            for (handCount = 1; handCount <= maxHandCount; handCount++) 
            {
                memcpy(state.hand[player], handCards, sizeof(int) * handCount);    
 
                for (deckCount = 1; deckCount <= maxDeckCount; deckCount++) 
                {
                    memcpy(state.deck[player], cards, sizeof(int) * deckCount);  
 
                    if (fullDeckCount(player, card, &state) == handCount + deckCount)
                        allPass = 1; 
                    else
                    {
                        allPass = 0;
                        break;
                    } 
                }
                if (!allPass)
                    break;
                clearCards(player, card, &state);
            }
            if (allPass)
                assertTest(1, &passedTests);
            else
                assertTest(0, &failedTests);

            clearCards(player, card, &state); 

            // TEST: Card in player's hand and discard, but not in deck 
            printf("-----------------------------------------------------------------------\n");   
            printf("    TEST: Card in player's hand and discard, but not in deck\n");
            printf("-----------------------------------------------------------------------\n"); 
 
            for (handCount = 1; handCount <= maxHandCount; handCount++)
            {
                memcpy(state.hand[player], handCards, sizeof(int) * handCount);  
     
                for (discardCount = 1; discardCount <= maxDiscardCount; discardCount++)
                {
                    memcpy(state.discard[player], cards, sizeof(int) * discardCount); 

                    if (fullDeckCount(player, card, &state) == handCount + discardCount)
                        allPass = 1; 
                    else
                    {
                        allPass = 0;
                        break;
                    } 
                }
                if (!allPass)
                    break;
                clearCards(player, card, &state);
            }
            if (allPass)
                assertTest(1, &passedTests);
            else
                assertTest(0, &failedTests);
            clearCards(player, card, &state); 
            
            // TEST: Card in player's deck and discard, but not in hand  
            printf("-----------------------------------------------------------------------\n");   
            printf("    TEST: Card in player's deck and discard, but not in hand\n"); 
            printf("-----------------------------------------------------------------------\n"); 
 
            for (deckCount = 1; deckCount <= maxDeckCount; deckCount++)
            {
                memcpy(state.deck[player], cards, sizeof(int) * deckCount);   
           
                for (discardCount = 1; discardCount <= maxDiscardCount; discardCount++)
                {
                    memcpy(state.discard[player], cards, sizeof(int) * discardCount); 
         
                    if (fullDeckCount(player, card, &state) == deckCount + discardCount)
                        allPass = 1; 
                    else
                    {
                        allPass = 0;
                        break;
                    } 
                }
                if (!allPass)
                    break;
                clearCards(player, card, &state);
            }
            if (allPass)
                assertTest(1, &passedTests);
            else
                assertTest(0, &failedTests);
            clearCards(player, card, &state);
    
            // TEST: Card in player's hand, deck, and discard
            printf("---------------------------------------------------------------------\n");    
            printf("    TEST: Card in player's hand, deck, and discard\n");
            printf("---------------------------------------------------------------------\n");  
 
            for (handCount = 1; handCount <= maxHandCount; handCount++)
            {
                memcpy(state.hand[player], handCards, sizeof(int) * handCount);  
 
                for (deckCount = 1; deckCount <= maxDeckCount; deckCount++)
                {
                    memcpy(state.deck[player], cards, sizeof(int) * deckCount);
                    memcpy(state.discard[player], cards, sizeof(int) * deckCount); 
          
                    if (fullDeckCount(player, card, &state) == handCount + 2 * deckCount)
                        allPass = 1; 
                    else
                    {
                        allPass = 0;
                        break;
                    } 
                }
                if (!allPass)
                    break;
                clearCards(player, card, &state);
            }
            if (allPass)
                assertTest(1, &passedTests);
            else
                assertTest(0, &failedTests);
            clearCards(player, card, &state);
        }
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

     

    
    


    
