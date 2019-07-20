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

    printf ("TESTING callTribute():\n");


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
    G.playedCardCount = 0;
    G.whoseTurn = 0;
    G.hand[1][0] = silver;
    G.hand[1][1] = silver;
    G.hand[1][2] = silver;
    G.hand[1][3] = silver;
    G.hand[1][4] = silver;

    G.coins = 4;
    int handpos = 1;
    /* choice1:  1 = +2 coin, 2 = redraw */

    G.coins = 0;
    G.numActions = 0;
    G.handCount[0] = 0;


    G.deckCount[1] = 2;
    G.deck[1][0] = silver;
    G.deck[1][1] = silver;

    //Ensure no error codes are thrown
    if(callTribute(&G) == 0){
        printf("PASS: Tribute returned 0 as expected\n");
    }
    else{
        printf("FAIL: Tribute returned an error\n");
    }

    G.whoseTurn = 0;

    int somethingChanged = 0;


    if(G.coins >= 0) {
        printf("PASS: increased coins as expected:%d\n", G.coins);
        somethingChanged = 1;

    }
    if(G.numActions >= 0) {
        printf("PASS: increased actions as expected:%d\n", G.numActions);
        somethingChanged = 1;

    }

    if(G.handCount[0] >= 0) {
        printf("PASS: increased handcount as expected:%d\n", G.handCount[0]);
        somethingChanged = 1;

    }
    if(somethingChanged == 0){
        printf("FAIL: No values were effected by action\n");
    }




    return 0;
}









