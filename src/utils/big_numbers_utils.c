#include "include/big_numbers_utils.h"


void bn_init_var(mpz_t var) {
    mpz_init(var);
}


void bn_free_var(mpz_t var) {
    mpz_clear(var);
}