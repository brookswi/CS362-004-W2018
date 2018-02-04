// Unit test for fullDeckCount function

/*
 * Include the following lines in your makefile:
 *
 * test_fullDeckCount: test_fullDeckCount.c dominion.o rngs.o
 *      gcc -o test_fullDeckCount -g  test_fullDeckCount.c dominion.o rngs.o $(CFLAGS)
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
    struct gameState state;

    int k[10] = {adventurer, council_room, feast, gardens, mine, remodel, smithy, village, baron, great_hall};
 
    // Game with max players 
    printf("Testing for game with 4 players\n\n");
    int retValue = initializeGame(MAX_PLAYERS, k, 1, &state);

    // Check that game is valid
    assert(retValue == 0);    

    int player, card, handCount, deckCount, discardCount; 
    int maxHandCount = 5;
    int maxDeckCount = 25;
    int maxDiscardCount = 30;
    for (player = 0; player < MAX_PLAYERS; player++)
    { 
        for (card = curse; card <= treasure_map; card++)
        {
            // Set all cards to a single card for uniformity
            clearCards(player, card, &state);           

            // TEST: None of current card in player's full deck
            printf("TEST: None of current card in full deck\n");

            state.handCount[player] = maxHandCount;
            state.deckCount[player] = maxDeckCount;
            state.discardCount[player] = maxDiscardCount;

            if (fullDeckCount(player, card, &state) == 0)
                assertTest(1);
            else
                assertTest(0); 
    
            // TEST: Card in player's hand, but not in deck or discard
            printf("TEST: Card in player's hand, but not in deck or discard\n");

            int i; 
            int handCards[MAX_HAND];
            for (i = 0; i < MAX_HAND; i++)
                handCards[i] = card;

            for (handCount = 0; handCount < maxHandCount; handCount++)
            {
                memcpy(state.hand[player], handCards, sizeof(int) * handCount);  

                if (fullDeckCount(player, card, &state) == handCount)
                    assertTest(1);
                else
                    assertTest(0); 
            }
            clearCards(player, card, &state); 

            // TEST: Card in player's deck, but not in hand or discard
            printf("TEST: Card in player's deck, but not in hand or discard\n");

            int cards[MAX_DECK];
            for (i = 0; i < MAX_DECK; i++)
                cards[i] = card;

            for (deckCount = 0; deckCount < maxDeckCount; deckCount++)
            {
                memcpy(state.deck[player], cards, sizeof(int) * deckCount);  

                if (fullDeckCount(player, card, &state) == deckCount)
                    assertTest(1);
                else
                    assertTest(0); 
            }
            clearCards(player, card, &state);

            // TEST: Card in player's discard, but not in hand or deck
            printf("TEST: Card in player's discard, but not in hand or deck\n");
            for (discardCount = 0; discardCount < maxDiscardCount; discardCount++)
            {
                memcpy(state.discard[player], cards, sizeof(int) * discardCount);  

                if (fullDeckCount(player, card, &state) == discardCount)
                    assertTest(1);
                else
                    assertTest(0); 
            }
            clearCards(player, card, &state);     

            // TEST: Card in player's hand and deck, but not in discard 
            printf("TEST: Card in player's hand and deck, but not in discard\n");
 
            for (handCount = 0; handCount < maxHandCount; handCount++) 
            {
                memcpy(state.hand[player], handCards, sizeof(int) * handCount);    
           
                for (deckCount = 0; deckCount < maxDeckCount; deckCount++) 
                {
                    memcpy(state.deck[player], cards, sizeof(int) * deckCount);  
          
                    if (fullDeckCount(player, card, &state) == handCount + deckCount)
                        assertTest(1);
                    else
                        assertTest(0); 
                }
                clearCards(player, card, &state);
            }
            clearCards(player, card, &state); 

            // TEST: Card in player's hand and discard, but not in deck 
            printf("TEST: Card in player's hand and discard, but not in deck\n");
 
            for (handCount = 0; handCount < maxHandCount; handCount++)
            {
                memcpy(state.hand[player], handCards, sizeof(int) * handCount);  
           
                for (discardCount = 0; discardCount < maxDiscardCount; discardCount++)
                {
                    memcpy(state.discard[player], cards, sizeof(int) * discardCount); 
          
                    if (fullDeckCount(player, card, &state) == handCount + discardCount)
                        assertTest(1);
                    else
                        assertTest(0); 
                }
                clearCards(player, card, &state);
            }
            clearCards(player, card, &state); 
            
            // TEST: Card in player's deck and discard, but not in hand 
            printf("TEST: Card in player's deck and discard, but not in hand\n");
 
            for (deckCount = 0; deckCount < maxDeckCount; deckCount++)
            {
                memcpy(state.deck[player], cards, sizeof(int) * deckCount);  
           
                for (discardCount = 0; discardCount < maxDiscardCount; discardCount++)
                {
                    memcpy(state.discard[player], cards, sizeof(int) * discardCount); 
          
                    if (fullDeckCount(player, card, &state) == deckCount + discardCount)
                        assertTest(1);
                    else
                        assertTest(0); 
                }
                clearCards(player, card, &state);
            }
            clearCards(player, card, &state);

            // TEST: Card in player's hand, deck, and discard
            printf("TEST: Card in player's hand, deck, and discard\n");
 
            for (handCount = 0; handCount < maxHandCount; handCount++)
            {
                memcpy(state.hand[player], handCards, sizeof(int) * handCount);  
           
                for (deckCount = 0; deckCount < maxDeckCount; deckCount++)
                {
                    memcpy(state.deck[player], cards, sizeof(int) * deckCount);
                    memcpy(state.discard[player], cards, sizeof(int) * deckCount); 
          
                    if (fullDeckCount(player, card, &state) == handCount + 2 * deckCount)
                        assertTest(1);
                    else
                        assertTest(0); 
                }
                clearCards(player, card, &state);
            }
            clearCards(player, card, &state);
        }
    }

    return 0;
}

     

    
    


    
