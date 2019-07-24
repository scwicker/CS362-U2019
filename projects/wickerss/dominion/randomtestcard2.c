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
#include <time.h>

// set NOISY_TEST to 0 to remove printfs from output
#define NOISY_TEST 1

int randomInt(int min, int max)
{
    int random_int, random_range;
    int the_min = min;
    int the_max = max;
    random_range = the_max - the_min;
    random_int = (rand() % (random_range)) + the_min;

    return random_int;
}

int main() {
    int i;
    int seed = 1000;
    int numPlayer = 4;
    int maxBonus = 10;
    int p, handCount;
    int bonus;
    int k[10] = {adventurer, council_room, feast, gardens, mine
            , remodel, smithy, village, baron, great_hall};
    struct gameState G;
    int maxHandCount = 5;
    // arrays of all coppers, silvers, and golds
    int coppers[MAX_HAND];

    for (i = 0; i < MAX_HAND; i++)
    {
        coppers[i] = copper;

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
                initializeGame(numPlayer, k, seed, &G); // initialize a new game
                G.handCount[p] = handCount;                 // set the number of cards on hand
                memcpy(G.hand[p], coppers, sizeof(int) * handCount); // set all the cards to copper
                updateCoins(p, &G, bonus);
#if (NOISY_TEST == 1)
#endif


            }
        }
    }



    int players;
    int handCounts;
    int supplyCount;
    int whoseTurn;
    int hand;
    int choice1;
    int choice2;
    int h;

    for (h = 0; h < 10000; h++) {
        players = randomInt(0, 4);
        handCounts = randomInt(0, 4);
        supplyCount = randomInt(0, 4);
        whoseTurn = randomInt(0, 4);
        hand = randomInt(0, 27);
        choice1 = randomInt(0, 2);
        choice2 = randomInt(0, 2);



        G.handCount[0] = handCounts;
        G.handCount[1] = handCounts;
        G.handCount[2] = handCounts;
        G.handCount[3] = handCounts;
        G.supplyCount[estate] = supplyCount;
        G.whoseTurn = players;
        // p > state->handCount[currentPlayer]
        G.hand[1][0] = randomInt(0, 27);
        G.hand[1][1] = randomInt(0, 27);
        G.hand[1][2] = hand;
        G.hand[1][3] = hand;
        G.hand[1][4] = hand;

        G.hand[0][0] = randomInt(0, 27);
        G.hand[0][1] = randomInt(0, 27);
        G.hand[0][2] = hand;
        G.hand[0][3] = hand;
        G.hand[0][4] = hand;

        G.hand[2][0] = randomInt(0, 27);
        G.hand[2][1] = randomInt(0, 27);
        G.hand[2][2] = hand;
        G.hand[2][3] = hand;
        G.hand[2][4] = hand;

        G.hand[3][0] = randomInt(0, 27);
        G.hand[3][1] = randomInt(0, 27);
        G.hand[3][2] = hand;
        G.hand[3][3] = hand;
        G.hand[3][4] = hand;
        G.numBuys = 2;


        printf("\n");
        printf("ROUND: %d\n", h);
        printf("players: %d\n", players);
        printf("handcount: %d\n", handCounts);
        printf("supplycount: %d\n", supplyCount);
        printf("whoseturn: %d\n", whoseTurn);
        printf("hand: %d\n", hand);
        printf("choice1: %d\n", choice1);
        printf("choice2: %d\n", choice2);
        

        if(callMinion(choice1, choice2, &G, handCounts) != 0){
            if (G.discard[1][0] == estate) {

                printf("Failure: See last inputs to troubleshoot.\n");
                break;

            }
        }
        else {
            printf("PASSED\n");
        }

    }




    ///////

    return 0;
}


