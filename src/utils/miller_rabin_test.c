#include "include/miller_rabin_test.h"


int miller_rabin(mpz_t n, mpz_t s, mpz_t d, mpz_t a, mpz_t i, mpz_t res, mpz_t temp, gmp_randstate_t randstate) {

    // Main logic.
    // -> Writing n - 1 = 2^sd, with d odd (Decomp method.)
    Decomp(n, s, d);

    // -> Choosing a randomly as : 1 < a < n - 1.
    generate_big_randomNumber_between_one_and_n_minus_one(n, randstate, a);

    // Computing a^d mod(n)
    ExpMod_GMP_style(n, a, d, res);     // Using the GMP method to make tests faster.

    if (mpz_cmpabs_ui(res, 1) == 0) {       // If res == -1 or 1
        // Probably primary, we stop.
        return 1;
    }

    mpz_set_ui(i, 1);       // i = 1

    while(mpz_cmp(i, s) < 0) {
        // Computing a^(d*2^i) mod(n)
        // -> Compute 2^i
        mpz_ui_pow_ui(temp, 2, mpz_get_ui(i));
        // -> Compute d * 2^i
        mpz_mul(temp, d, temp);
        // -> Compute a^(d * 2^i) mod n
        ExpMod(n, a, temp, res);

        // If it is = -1 mod n, probably primary.
        if (mpz_cmp_ui(res, -1) == 0) {
            return 1;
        } 
        // If it is = -1 mod n, not primary.
        if (mpz_cmp_ui(res, 1) == 0) {
            return 0;
        } 

        mpz_add_ui(i, i, 1);    // i += 1
    }

    // If we arrive here, and that a^(d2^i) != 1 mod n, n is not primary. We stop.
    return 0;
}


int MillerRabin(mpz_t n, gmp_randstate_t randstate, int cpt) {
    int iter = 0;

    // Variables initialization.
    mpz_t s, d, a, i, res, temp;
    mpz_inits(s, d, a, i, res, temp, NULL);

    while (iter < cpt) {
        if (!miller_rabin(n, s, d, a, i, res, temp, randstate)) {
            // We found a decomposition. The number is composite.
            return 0;
        }
        iter ++;
    }

    mpz_clears(s, d, a, i, res, temp, NULL);

    // If we reached here, we did not find a composite for the number, it is probably primary.
    return 1;
}


int Eval(gmp_randstate_t randstate, int cpt, int b, const int fast_mode) {
    // Variables
    int i = 0;
    mpz_t random_number;    mpz_init(random_number);

    generate_big_randomNumber(b, randstate, random_number);

    if (fast_mode) {
        while(mpz_probab_prime_p(random_number, 20) == 0) {
            i++;
            generate_big_randomNumber(b, randstate, random_number);
        }
    } else {
        while(MillerRabin(random_number, randstate, cpt) == 0) {
            i++;
            generate_big_randomNumber(b, randstate, random_number);
        }
    }

    mpz_clear(random_number);
    return i;
}