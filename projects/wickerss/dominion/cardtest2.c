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

    printf ("TESTING shuffle():\n");


    memset(&G, 23, sizeof(struct gameState));   // clear the game state
    initializeGame(numPlayer, k, seed, &G); // initialize a new game


    G.deckCount[0] = 4;
    r = shuffle(0, &G);

    if (r == 0){
        printf("PASS: shuffle  returned no errors with good params\n");
    }
    else{
        printf("FAIL: shuffle  returned non 0 exit with good params.\n");
    }



    G.deckCount[0] = 0;
    r = shuffle(0, &G);

    if (r == -1){
        printf("PASS: shuffle caught empty deck error \n");
    }
    else{
        printf("FAIL: shuffle did not catch empty deck error.\n");
    }


    //state->deck[player][card];
    G.deckCount[0] = 5;
    G.deck[0][1] = silver;
    G.deck[0][2] = copper;
    G.deck[0][3] = gold;
    G.deck[0][4] = estate;
    G.deck[0][5] = province;
    r = shuffle(0, &G);
    
    int similarity;
    G.deck[1][1] = silver;
    G.deck[1][2] = silver;
    G.deck[1][3] = silver;
    G.deck[1][4] = silver;
    G.deck[1][5] = silver;
    
    for(r = 1; r < 6; r++){
        if (G.deck[0][r] == G.deck[1][r]){
            similarity += 1;
        }
    }
    
    printf("PASS: %d positions were similar after shuffle\n", similarity);

    return 0;
}
