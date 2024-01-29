#include <stdio.h>
#include <stdlib.h>

#include "include/constants.h"
#include "utils/include/random_utils.h"
#include "utils/include/big_numbers_utils.h"


int main() {

    printf("# ---- Welcome ! ---- #\n\n");

    mpz_t random_number_1;
    mpz_t random_number_2;
    generate_big_randomNumber(150, random_number_1);
    generate_big_randomNumber(150, random_number_2);

    mpz_t rop;
    init_variable_for_big_numbers(rop);
    
    mpz_add(rop, random_number_1, random_number_2);

    gmp_printf("Operation : %Zd + %Zd = %Zd\n", random_number_1, random_number_2, rop);

    printf("\n# ---- Goodbye ! ---- #\n\n");
    return 0;
}
