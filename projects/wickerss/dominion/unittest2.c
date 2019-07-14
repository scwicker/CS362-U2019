/* -----------------------------------------------------------------------
 * Demonstration of how to write unit tests for dominion-base
 * Include the following lines in your makefile:
 *
 * testUpdateCoins: testUpdateCoins.c dominion.o rngs.o
 *      gcc -o testUpdateCoins -g  testUpdateCoins.c dominion.o rngs.o $(CFLAGS)
 * -----------------------------------------------------------------------
 */

#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"

// set NOISY_TEST to 0 to remove printfs from output
#define NOISY_TEST 1

int main() {
    int i;
    int seed = 1000;
    int numPlayer = 2;
    int maxBonus = 10;
    int p, r, handCount;
    int bonus;
    int k[10] = {adventurer, council_room, feast, gardens, mine
            , remodel, smithy, village, baron, great_hall};
    struct gameState G;
    int maxHandCount = 5;
    // arrays of all coppers, silvers, and golds
    int coppers[MAX_HAND];
    int silvers[MAX_HAND];
    int golds[MAX_HAND];
    for (i = 0; i < MAX_HAND; i++)
    {
        coppers[i] = copper;
        silvers[i] = silver;
        golds[i] = gold;
    }

    printf ("TESTING callMinion():\n");


    for (p = 0; p < numPlayer; p++)
    {
        for (handCount = 1; handCount <= maxHandCount; handCount++)
        {
            for (bonus = 0; bonus <= maxBonus; bonus++)
            {
#if (NOISY_TEST == 1)
#endif
                memset(&G, 23, sizeof(struct gameState));   // clear the game state
                r = initializeGame(numPlayer, k, seed, &G); // initialize a new game
                G.handCount[p] = handCount;                 // set the number of cards on hand
                memcpy(G.hand[p], coppers, sizeof(int) * handCount); // set all the cards to copper
                updateCoins(p, &G, bonus);
#if (NOISY_TEST == 1)
#endif


            }
        }
    }

    G.whoseTurn = 1;
    int tempCoins;
    tempCoins = G.coins;
    callMinion(1, 0, &G, 1);
    if (tempCoins + 2 == G.coins){

        printf("PASS: option 1 added coins as expected.\n");
    }



    G.whoseTurn = 1;
    tempCoins = G.coins;
    callMinion(0, 1, &G, 1);
    if (tempCoins == G.coins){

        printf("PASS: option 2 skipped adding coins as expected.\n");
    }




    G.whoseTurn = 1;
    G.handCount[1] = 4;
    callMinion(0, 1, &G, 1);
    if (G.handCount[1] == 4){

        printf("PASS: option 2 discarded and drew 4 new cards\n");
    }
    else{
        printf("FAILED: option 2 should have drew 4 new cards for current player\n");
    }

    G.whoseTurn = 1;
    G.handCount[0] = 3;
    G.deckCount[0] = 10;
    callMinion(0, 1, &G, 1);
    if (G.handCount[0] == 3){

        printf("PASS: option 2 ignored hand count less than 4\n");
    }
    else{
        printf("FAILED: Should not have redrawn for players with less than 4 cards\n");
    }



    G.whoseTurn = 1;
    G.handCount[0] = 8;
    G.deckCount[0] = 10;
    callMinion(0, 1, &G, 1);
    G.whoseTurn = 0;
    if (numHandCards(&G) == 4){

        printf("PASS: drew new cards for player over 5\n");
    }
    else{
        printf("FAILED: Should  have redrawn for players with more than 5 cards\n");
    }


    return 0;
}


