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
    // arrays of all coppers, silvers, and golds

    // initializeGame(int numPlayers, int kingdomCards[10], int randomSeed, struct gameState *state)

    printf ("TESTING initializeGame():\n");

    memset(&G, 23, sizeof(struct gameState));   // clear the game state
    r = initializeGame(numPlayer, k, seed, &G); // initialize a new game

    if (r == 0){
        printf("PASS: initialize game returned no errors with good params\n");
    }
    else{
        printf("FAIL: initialize game returned non 0 exit with good params.\n");
    }



    numPlayer = 6;
    r = initializeGame(numPlayer, k, seed, &G); // initialize a new game
    if (r == -1){
        printf("PASS: initialize game caught too many players error\n");
    }
    else{
        printf("FAIL: initialize game did not catch too many players.\n");
    }



    numPlayer = 3;
    r = initializeGame(numPlayer, k, seed, &G); // initialize a new game
    if (G.numPlayers == 3){
        printf("PASS: Set number of players correctly in GameState instance\n");
    }
    else{
        printf("FAIL: set wrong number of players in game state instance .\n");
    }


    if (G.supplyCount[curse] == 20){
        printf("PASS: assert supply count of curse equals 20\n");
    }
    else{
        printf("FAIL: curse supply count assertion not equal to 20 .\n");
    }

    if (G.supplyCount[copper] == 39){
        printf("PASS: assert supply count of copper = 39.  Copper returned: %d\n", G.supplyCount[copper]);
    }
    else{
        printf("FAIL: copper did not supply the correct amount of 39 for 3 players.\n");
    }


    if (G.embargoTokens[0] == 0){
        printf("PASS: Embargo tokens set to 0 as expected\n");
    }
    else{
        printf("FAIL: Embargo tokens not set to 0 as expected\n");
    }


    return 0;
}
