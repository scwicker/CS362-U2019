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

    printf ("TESTING callMine():\n");


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

 G.whoseTurn = 1;
 //state->hand[player][count]
 G.hand[1][1] = province; //8
 G.hand[1][2] = estate;   //3

 //int i, int j, int choice1, int choice2, int currentPlayer, struct gameState *state, int handPos
 if(callMine( 1, 1, 1, 2, 1, &G, bonus) == -1){
     printf("PASS: Caught card outside of silver, copper, gold range.\n");
 }
 else{
     printf("Failed: callMine should have caught this error \n");
 }

    //should fail because it's greater than gold
    G.hand[1][1] = adventurer;
    G.whoseTurn = 1;
    if(callMine(1, 1, 2, 1, 2, &G, bonus) == -1){
        printf("PASS: Caught card outside of silver, copper, gold range.\n");
    }else{
        printf("Failed: callMine\n");
    }

    //should pass
    G.hand[1][1] = silver;
    G.hand[1][2] = province;
    G.whoseTurn = 1;
    if(callMine(1, 1, 2, 1, 2, &G, bonus) == 0){
        printf("PASS: Card validated inside of range.\n");
    }
    else{
        printf("Failed: callMine\n");
    }

    //should pass
    G.hand[1][2] = outpost;
    G.whoseTurn = 1;
    if(callMine(1, 1, 2, 1, 2, &G, bonus) == 0){
        printf("PASS: Card validated inside of range curse - treasure map.\n");
    }
    else{
        printf("Failed: callMine\n");
    }




    G.hand[1][1] = copper;
    G.hand[1][2] = 100;
    G.whoseTurn = 1;
    if(callMine(1, 1, 2, 1, 2, &G, bonus) == -1){
        printf("PASS: Caught card out of range curse - treasure range.\n");
    }
    else{
        printf("Failed: callMine from curse - treasuremap\n");
    }

    G.whoseTurn = 1;
    G.hand[1][1] = silver;
    G.hand[1][2] = province;
    G.playedCardCount = 10;
    callMine(1, 1, 2, 1, 2, &G, bonus);
    if(G.playedCardCount == 10){
        printf("PASS: Card was trashed (as expected) instead of added to played cards.\n");
    }
    else{
        printf("Failed: callMine did not Trash card\n");
    }

    printf("All tests passed!\n");

    return 0;
}



