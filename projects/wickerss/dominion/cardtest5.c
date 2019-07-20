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
    int i;
    int seed = 1000;
    int numPlayer = 2;
    int k[10] = {adventurer, council_room, feast, gardens, mine
            , remodel, smithy, village, baron, great_hall};
    struct gameState G;






    // int shuffle(int player, struct gameState *state)

    printf ("TESTING drawCard():\n");
//
//
    memset(&G, 23, sizeof(struct gameState));   // clear the game state
    initializeGame(numPlayer, k, seed, &G); // initialize a new game
//



    G.handCount[0] = 5;
    G.deckCount[0]= 13;

    G.deck[0][0] = adventurer;
    G.deck[0][1] = council_room;
    G.deck[0][2] = province;
    G.deck[0][3] = estate;
    G.deck[0][4] = baron;
    G.deck[0][5] = remodel;
    G.deck[0][6] = smithy;
    G.deck[0][7] = village;
    G.deck[0][8] = gold;
    G.deck[0][9] = silver;
    G.deck[0][10] = province;
    G.deck[0][11] = village;
    G.deck[0][12] = mine;

    G.discardCount[0] = 6;

    G.discard[0][0] = village;
    G.discard[0][1] = gold;
    G.discard[0][2] = silver;
    G.discard[0][3] = province;
    G.discard[0][4] = village;
    G.discard[0][5] = mine;



    // test return 0 good params
    r = drawCard(0, &G);
    if (r == 0){
        printf("PASS: draw cards returned no errors with good params\n");
    }
    else{
        printf("FAIL: draw cards returned non 0 exit with good params.\n");
    }


    // test increase by 1
    r = drawCard(0, &G);

    if(G.handCount[0] > 5){
        printf("PASS: Hand count increased by one after a draw as expected.\n");
    }
    else{
        printf("FAIL: Hand count did not increase by one after a draw.\n");
    }


    // test randomness of draw

    r = drawCard(0, &G);

    if(G.hand[0][5] == G.hand[0][6] &&  G.hand[0][5] == G.hand[0][7]){
        printf("FAIL: Draw card returned same card 3 times in a row.\n");
    }
    else{
        printf("PASS: Cards are shuffled and drawn randomly.\n");
    }



    return 0;
}
