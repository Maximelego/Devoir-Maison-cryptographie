#include "include/miller_rabin_test.h"


int miller_rabin(mpz_t n, const unsigned long cpt, gmp_randstate_t randstate) {

    // Variables initialization.
    mpz_t s;        bn_init_var(s);
    mpz_t d;        bn_init_var(d);
    mpz_t a;        bn_init_var(a);
    mpz_t i;        bn_init_var(i);
    mpz_t res;      bn_init_var(res);

    // Main logic.
    // -> Writing n - 1 = 2^sd, with d odd (Decomp method.)
    Decomp(n, s, d);

    // -> Choosing a randomly as : 1 < a < n - 1.
    generate_big_randomNumber_between_one_and_n_minus_one(n, randstate, a);

    // Computing a^d mod(n)
    ExpMod(n, a, d, res);

    if (mpz_cmp_ui(res, 1) || mpz_cmp_ui(res, -1)) {
        // Probably primary, we stop.
        return 1;
    }

    mpz_set_ui(i, 1);       // i = 1
    while(mpz_cmp(i, s)) {
        // Computing a^(d2)^i mod(n)
        
    }

    // Freeing variables
    bn_free_var(s);
    bn_free_var(d);
    bn_free_var(a);
    bn_free_var(i);
    bn_free_var(res);
}
