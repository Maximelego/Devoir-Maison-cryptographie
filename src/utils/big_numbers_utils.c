#include "include/big_numbers_utils.h"


void bn_init_var(mpz_t var) {

    if (DEBUG_MODE) { 
        printf("[INFO] - (init_variable_for_big_numbers) Preparing var ...\n");
    }
    
    mpz_init(var);

    if (DEBUG_MODE) { 
        printf("[INFO] - (init_variable_for_big_numbers) Done !\n");
    }
}


void bn_free_var(mpz_t var) {
    if (DEBUG_MODE) { 
        printf("[INFO] - (free_variable_for_big_numbers) Freeing var ...\n");
    }

    mpz_clear(var);

    if (DEBUG_MODE) { 
        printf("[INFO] - (free_variable_for_big_numbers) Done !\n");
    }
}


void bn_add(const mpz_t op1, const mpz_t op2, mpz_t result) {
    if (DEBUG_MODE) { 
        printf("[INFO] - (add_big_numbers) Starting operation ...\n");
    }

    bn_init_var(result);
    mpz_add(result, op1, op2);

    if (DEBUG_MODE) { 
        printf("[INFO] - (free_variable_for_big_numbers) ");
        gmp_printf("Operation : %Zd + %Zd = %Zd\n", op1, op2, result);
    }
}