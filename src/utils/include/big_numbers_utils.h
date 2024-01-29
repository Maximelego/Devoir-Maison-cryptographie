#ifndef BIG_NUMBER_UTILS
#define BIG_NUMBER_UTILS

#include <stdio.h>

#include "gmp.h"
#include "include/constants.h"

// Initialization and freeing for the GMP Variables
void init_variable_for_big_numbers(mpz_t var);
void free_variable_for_big_numbers(mpz_t var);

// Supersets of operations.
void add_big_numbers(mpz_t result, mpz_t op1, mpz_t op2);


#endif  // BIG_NUMBER_UTILS