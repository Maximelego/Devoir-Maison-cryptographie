//
// Created by maiso on 23/01/2024.
//

#ifndef PROJET_RANDOM_UTILS_H
#define PROJET_RANDOM_UTILS_H

#include <stdio.h>
#include <stdlib.h>

#include "gmp.h"
#include "../../include/constants.h"

void generate_big_randomNumber(unsigned long size, gmp_randstate_t randstate, mpz_t number);
void generate_big_randomNumber_between_one_and_n_minus_one(mpz_t upper_bound, gmp_randstate_t randstate, mpz_t number);

#endif //PROJET_RANDOM_UTILS_H
