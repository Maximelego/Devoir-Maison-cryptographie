//
// Created by maiso on 23/01/2024.
//

#include "include/random_utils.h"


void generate_big_randomNumber(const unsigned long size, gmp_randstate_t randstate, mpz_t number) {
    mpz_urandomb(number, randstate, size);
}


void generate_big_randomNumber_between_one_and_n_minus_one(mpz_t upper_bound, gmp_randstate_t randstate, mpz_t number) {
    mpz_t n_minus_one;  mpz_init(n_minus_one);
    
    mpz_sub_ui(n_minus_one, upper_bound, 1);
    mpz_urandomm(number, randstate, n_minus_one);
    mpz_add_ui(number, number, 2);

    mpz_clear(n_minus_one);
}