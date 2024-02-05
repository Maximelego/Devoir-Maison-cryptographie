#ifndef MILLER_RABIN_TEST
#define MILLER_RABIN_TEST

#include "gmp.h"
#include "decomposition.h"
#include "random_utils.h"

int miller_rabin(mpz_t n, gmp_randstate_t randstate);
int MillerRabin(mpz_t n, gmp_randstate_t randstate, int cpt);

#endif