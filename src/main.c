#include <stdio.h>
#include <stdlib.h>

#include "include/constants.h"
#include "utils/include/random_utils.h"
#include "utils/include/big_numbers_utils.h"


int main() {

    printf("# ---- Welcome ! ---- #\n\n");

    mpz_t random_number_1;
    mpz_t random_number_2;
    generate_big_randomNumber(2048, random_number_1);
    generate_big_randomNumber(2048, random_number_2);

    mpz_t rop;
    add_big_numbers(rop, random_number_1, random_number_2);

    printf("\n# ---- Goodbye ! ---- #\n\n");
    return 0;
}
