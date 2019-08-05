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

    printf ("TESTING callAmbassador():\n");


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

    G.numPlayers = 2;
    G.whoseTurn = 1;
    G.hand[1][0] = ambassador;
    G.hand[1][1] = copper;
    G.hand[1][2] = province;
    G.hand[1][3] = estate;
    G.hand[1][4] = estate;
    G.handCount[1] = 5;

    G.coins = 4;
/* choice1 = card your getting rid of, choice2 = number of that card to return to supply */


    if (callAmbassador(1, 1, 3, 3, 1, &G, 0) == -1) {

        printf("PASS: Caught number out of range 0-2 and returned -1\n");
    }
    else {
        printf("FAIL: Did not catch choice two out of range 0-2\n");
    }

    if (callAmbassador(1, 1, 1, 2, 1, &G, 0) == -1) {

        printf("PASS: Caught Hand position can not equal choice 1\n");
    }
    else {
        printf("FAIL: Did not catch Hand position can not equal choice 1\n");
    }


    if (callAmbassador(1, 1, 3, 1, 1, &G, 0) == 0) {

        printf("PASS: should pass parameters in range\n");
    }
    else {
        printf("FAIL: bug did not allow good params to pass\n");
    }



    G.whoseTurn = 1;
    G.hand[1][0] = ambassador;
    G.hand[1][1] = copper;
    G.hand[1][2] = province;
    G.hand[1][3] = estate;
    G.hand[1][4] = estate;

    G.hand[0][0] = silver;
    G.hand[0][1] = silver;
    G.hand[0][2] = silver;
    G.hand[0][3] = silver;
    G.hand[0][4] = silver;

    G.handCount[1] = 5;

    G.numPlayers = 2;
    G.handCount[0]= 5;
    int previous_discard_count = G.discardCount[0];
    callAmbassador(1, 1, 3, 1, 1, &G, 0);


    //make sure both cards were discarded
    if(G.hand[1][3] == -1 && G.hand[1][4] == -1) {
        printf("PASS: Estate card removed from hand\n");

    }
    else {
        printf("FAIL: Should have removed estates from hand\n");
    }


    if(previous_discard_count == G.discardCount[0]) {
        printf("FAIL: discard count should have increased for opponent by 1\n");
    }
    else if(previous_discard_count == G.discardCount[0] + 1) {
        printf("PASS: The discard count of opponenet increased as expected\n");
    }

    //added card for [whoseTurn] current player:
    // toFlag = 0 : add to discard
    // toFlag = 1 : add to deck
    // toFlag = 2 : add to hand
    //THIS SHOULD PROBABLY BE GAIN A CARD FOR OPPONENT, CHANGING TO i


    for(i = 0; i < G.discardCount[0]; i++) {
        if(G.discard[0][i] == estate) {

            printf("PASS: opponent gained a copy of the card in discard pile : %d\n", G.discard[0][i]);
        }
        else{
            printf("FAIL: Opponent should have gained the card in discard pile\n");
        }

    }


    return 0;
}
