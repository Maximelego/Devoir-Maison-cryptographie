#ifndef BIG_NUMBER_UTILS
#define BIG_NUMBER_UTILS

#include <stdio.h>

#include "gmp.h"
#include "include/constants.h"

// Initialization and freeing for the GMP Variables
void bn_init_var(mpz_t var);
void bn_free_var(mpz_t var);

// Supersets of operations.
void bn_add(const mpz_t op1, const mpz_t op2, mpz_t result);


#endif  // BIG_NUMBER_UTILS