#include <stdio.h>
#include <stdlib.h>

#include "include/constants.h"
#include "utils/include/random_utils.h"
#include "utils/include/big_numbers_utils.h"
#include "utils/include/decomposition.h"


void init_randstate(gmp_randstate_t randstate) {
    gmp_randinit_default(randstate);
    gmp_randseed_ui(randstate, RANDOM_SEED);
}


void try_n_decomp(const unsigned long n, gmp_randstate_t randstate) {
    // Variables initialization.
    unsigned long i = 0;
    FILE* file;
    mpz_t random_number; bn_init_var(random_number);
    mpz_t s;             bn_init_var(s);
    mpz_t d;             bn_init_var(d);

    if (LOG_TO_FILE) {
        file = fopen("output.txt", "w");
    }

    // Doing the N loop.
    while (i < n) {
        generate_big_randomNumber(RANDOM_NUMBERS_SIZE, randstate, random_number);
        Decomp(random_number, s, d);
        // print_decomp(random_number, s, d);

        if (LOG_TO_FILE) { 
            log_decomp_to_file(random_number, s, d, file); 
        }

        i ++;
    }

    // Freeing vars.
    bn_free_var(random_number);
    bn_free_var(s);
    bn_free_var(d);

    if (LOG_TO_FILE) {
        fclose(file);
    }
}

void try_n_exp_mod(const unsigned long n, gmp_randstate_t randstate) {
    
}



int main() {

    printf("# ---- Welcome ! ---- #\n\n");

    gmp_randstate_t randstate; 
    init_randstate(randstate);

    try_n_decomp(10000, randstate);    

    printf("\n# ---- Goodbye ! ---- #\n\n");
    return 0;
}
