//
// Created by maiso on 23/01/2024.
//

#include "include/random_utils.h"
#include "gmp.h"


void generate_big_randomNumber(int size) {

    if (DEBUG_MODE) { 
        printf("[INFO] - (generate_big_randomNumber) Starting the generation of a random number ...\n");
        printf("[INFO] - (generate_big_randomNumber) Number's size : %i\n", size);
        printf("[INFO] - (generate_big_randomNumber) Initializing random seed...\n");
    }

    gmp_randstate_t randstate;
    gmp_randinit_default(randstate);

    if (DEBUG_MODE) { 
        printf("[INFO] - (generate_big_randomNumber) Generating random number...\n");
    }

    

}