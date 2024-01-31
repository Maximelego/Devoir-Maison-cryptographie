#ifndef MILLER_RABIN_TEST
#define MILLER_RABIN_TEST

#include "gmp.h"
#include "big_numbers_utils.h"
#include "decomposition.h"
#include "random_utils.h"

void miller_rabin(mpz_t n, const unsigned long cpt, gmp_randstate_t randstate);

#endif