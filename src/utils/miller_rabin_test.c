#include "include/miller_rabin_test.h"

void free_miller_rabin_vars(mpz_t s, mpz_t d, mpz_t a, mpz_t i, mpz_t res, mpz_t temp) {
    mpz_clear(s);
    mpz_clear(d);
    mpz_clear(a);
    mpz_clear(i);
    mpz_clear(res);
    mpz_clear(temp);
}


int miller_rabin(mpz_t n, gmp_randstate_t randstate) {

    // Variables initialization.
    mpz_t s;            mpz_init(s);
    mpz_t d;            mpz_init(d);
    mpz_t a;            mpz_init(a);
    mpz_t i;            mpz_init(i);
    mpz_t res;          mpz_init(res);
    mpz_t temp;         mpz_init(temp);

    // Main logic.
    // -> Writing n - 1 = 2^sd, with d odd (Decomp method.)
    Decomp(n, s, d);

    // -> Choosing a randomly as : 1 < a < n - 1.
    generate_big_randomNumber_between_one_and_n_minus_one(n, randstate, a);

    // Computing a^d mod(n)
    ExpMod(n, a, d, res);

    if (mpz_cmp_ui(res, 1) || mpz_cmp_ui(res, -1)) {
        // Probably primary, we stop.
        free_miller_rabin_vars(s, d, a, i, res, temp);
        return 1;
    }

    mpz_set_ui(i, 1);       // i = 1

    while(mpz_cmp(i, s) != 0) {
        // Computing a^(d*2^i) mod(n)
        // -> Compute 2^i
        mpz_ui_pow_ui(temp, 2, mpz_get_ui(i));
        // -> Compute d * 2^i
        mpz_mul(temp, d, temp);
        // -> Compute a^(d * 2^i) mod n
        ExpMod(n, a, temp, res);

        // If it is = -1 mod n, probably primary.
        if (mpz_cmp_ui(res, -1)) {
            free_miller_rabin_vars(s, d, a, i, res, temp);
            return 1;
        } 
        // If it is = -1 mod n, not primary.
        if (mpz_cmp_ui(res, 1)) {
            free_miller_rabin_vars(s, d, a, i, res, temp);
            return 0;
        } 

        mpz_add_ui(i, i, 1);    // i += 1
    }

    // If we arrive here, and that a^(d2^i) != 1 mod n, n is not primary. We stop.
    free_miller_rabin_vars(s, d, a, i, res, temp);
    return 0;
}


int MillerRabin(mpz_t n, gmp_randstate_t randstate, int cpt) {
    int i = 0;
    while (i < cpt) {
        if (!miller_rabin(n, randstate)) {
            // We found a decomposition. The number is composite.
            return 0;
        }
        i++;
    } 

    // If we reached here, we did not found a composite for the number, it is probably primary.
    return 1;
}