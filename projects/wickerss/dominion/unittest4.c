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
    G.playedCardCount = 1;
    G.whoseTurn = 1;
    G.hand[1][0] = silver;
    G.hand[1][1] = silver;
    G.hand[1][2] = silver;
    G.hand[1][3] = silver;
    G.hand[1][4] = silver;

    G.coins = 4;
    int handpos = 1;
    /* choice1:  1 = +2 coin, 2 = redraw */
    callMinion(1, 0, &G, handpos);

    if(G.coins == 6) {
        printf("PASS: increased 2 coins as expected.\n");

    }
    else {
        printf("FAILED: Should have increased 2 coins\n");
    }





    //see if hand was discraded and re drawn

    G.playedCardCount = 5;
    G.whoseTurn = 1;
    G.hand[1][0] = silver;
    G.hand[1][1] = silver;
    G.hand[1][2] = silver;
    G.hand[1][3] = silver;
    G.hand[1][4] = silver;

    handpos = 1;
    /* choice1:  1 = +2 coin, 2 = redraw */
    callMinion(0, 1, &G, handpos);
    for(i = 0; i < 5; i++) {

        if (G.hand[1][i] != silver) {
            printf("PASS: Card %d is no longer silver, therefore redrawn.\n", i);

        } else {
            printf("FAILED: Or possible redrew silver\n");
        }
    }


    // test that player with less than four cards do not re draw

    G.handCount[1] = 5;
    G.whoseTurn = 1;
    G.hand[1][0] = silver;
    G.hand[1][1] = silver;
    G.hand[1][2] = silver;
    G.hand[1][3] = silver;
    G.hand[1][4] = silver;


    G.hand[0][0] = silver;
    G.hand[0][1] = silver;
    G.hand[0][2] = silver;
    G.handCount[0] = 3;

    handpos = 1;
    /* choice1:  1 = +2 coin, 2 = redraw */
    callMinion(0, 1, &G, handpos);
    for(i = 0; i < 3; i++) {

        if (G.hand[0][i] != silver) {
            printf("FAIL: Card %d is no longer silver, therefore redrawn.\n", i);
            break;

        } else {
            printf("PASS: Other play hand remaines unchanged.\n");
        }
    }




    return 0;
}









