#ifndef BIG_NUMBER_UTILS
#define BIG_NUMBER_UTILS

#include <stdio.h>

#include "gmp.h"
#include "include/constants.h"

mpz_t* init_variable_for_big_numbers();
void free_variable_for_big_numbers(mpz_t* var);

#endif  // BIG_NUMBER_UTILS