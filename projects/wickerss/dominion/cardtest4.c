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


int main() {
    int r;
    int seed = 1000;
    int numPlayer = 4;
    int k[10] = {adventurer, council_room, feast, gardens, mine
            , remodel, smithy, village, baron, great_hall};
    struct gameState G;

    // int shuffle(int player, struct gameState *state)

    printf ("TESTING getWinners():\n");
//
//
    memset(&G, 23, sizeof(struct gameState));   // clear the game state
    initializeGame(numPlayer, k, seed, &G); // initialize a new game
//
    int players[4];
    players[0] = 1;
    players[1] = 1;
    players[2] = 1;
    players[3] = 1;

    G.deckCount[0] = 1;
    G.deckCount[1] = 1;
    G.deckCount[2] = 1;
    G.deckCount[3] = 1;

    G.deck[0][0] = estate;
    G.deck[1][0] = estate;
    G.deck[2][0] = estate;
    G.deck[3][0] = estate;

    G.handCount[0] = 1;
    G.handCount[1] = 1;
    G.handCount[2] = 1;
    G.handCount[3] = 1;

    G.hand[0][0] = estate;
    G.hand[1][0] = estate;
    G.hand[2][0] = estate;
    G.hand[3][0] = estate;

    G.discardCount[0] = 1;
    G.discardCount[1] = 3;
    G.discardCount[2] = 2;
    G.discardCount[3] = 1;

    G.discard[0][0] = estate;
    G.discard[0][1] = estate;
    G.discard[0][2] = estate;
    G.discard[0][3] = estate;
    G.discard[0][4] = estate;
    G.discard[0][5] = estate;
    G.discard[1][0] = estate;
    G.discard[1][1] = estate;
    G.discard[1][2] = estate;
    G.discard[2][0] = estate;
    G.discard[2][1] = estate;
    G.discard[3][0] = estate;
    G.discard[3][1] = estate;



    r = getWinners(players, &G);
    if (r == 0){
        printf("PASS: get winners returned no errors with good params\n");
    }
    else{
        printf("FAIL: get winners returned non 0 exit with good params.\n");
    }


    int i;

    if(players[1] == 1 && players[0] == 0 && players[2] == 0 && players[3] == 0) {
        for (i = 0; i < 4; i++) {
            printf("PASS: player[%d] win point: %d \n", i, players[i]);
        }
    }
    else{
        printf("FAIL: Player[1] should have been the winner");
    }

    return 0;
}
