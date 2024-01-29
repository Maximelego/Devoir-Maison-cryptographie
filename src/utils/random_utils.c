//
// Created by maiso on 23/01/2024.
//

#include "include/random_utils.h"
#include "include/big_numbers_utils.h"


void generate_big_randomNumber(const unsigned long size, gmp_randstate_t randstate, mpz_t number) {

    if (DEBUG_MODE) { 
        printf("[INFO] - (generate_big_randomNumber) Generating random number...\n");
    }

    mpz_urandomb(number, randstate, size);
}