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
    int r;
    int seed = 1000;
    int numPlayer = 2;
    int k[10] = {adventurer, council_room, feast, gardens, mine
            , remodel, smithy, village, baron, great_hall};
    struct gameState G;

    // int shuffle(int player, struct gameState *state)

    printf ("TESTING endTurn():\n");


    memset(&G, 23, sizeof(struct gameState));   // clear the game state
    initializeGame(numPlayer, k, seed, &G); // initialize a new game


    G.deckCount[0] = 4;
    G.handCount[0] = 5;
    r = endTurn(&G);
    if (r == 0){
        printf("PASS: end turn  returned no errors with good params\n");
    }
    else{
        printf("FAIL: end turn  returned non 0 exit with good params.\n");
    }

    G.whoseTurn = 0;
    r = endTurn(&G);
    if (G.handCount[0] == 0){
        printf("PASS: reset hand count successfully \n");
    }
    else{
        printf("FAIL: did not reset hand count.\n");
    }


    //state->deck[player][card];
    G.deckCount[0] = 5;
    G.hand[0][1] = silver;
    G.hand[0][2] = silver;
    G.hand[0][3] = silver;
    G.hand[0][4] = silver;
    G.hand[0][5] = silver;
    
    G.numBuys = 2;
    r = endTurn(&G);

    int similarity;
    G.hand[1][1] = silver;
    G.hand[1][2] = silver;
    G.hand[1][3] = silver;
    G.hand[1][4] = silver;
    G.hand[1][5] = silver;

    for(r = 1; r < 6; r++){
        if (G.hand[0][r] == G.hand[1][r]){
            similarity += 1;
        }
    }

    printf("PASS: %d positions were similar after end turn\n", similarity);


    if (G.numBuys == 1){
        printf("PASS: number of buys successfully reset during end turn\n");
    }
    else{
        printf("FAIL: number of buys not reset during end turn.\n");
    }

    
    return 0;
}
