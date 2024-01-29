#include "include/big_numbers_utils.h"


void init_variable_for_big_numbers(mpz_t var) {

    if (DEBUG_MODE) { 
        printf("[INFO] - (init_variable_for_big_numbers) Preparing var ...\n");
    }
    
    mpz_init(var);

    if (DEBUG_MODE) { 
        printf("[INFO] - (init_variable_for_big_numbers) Done !\n");
    }
}


void free_variable_for_big_numbers(mpz_t var) {
    if (DEBUG_MODE) { 
        printf("[INFO] - (free_variable_for_big_numbers) Freeing var ...\n");
    }

    mpz_clear(var);

    if (DEBUG_MODE) { 
        printf("[INFO] - (free_variable_for_big_numbers) Done !\n");
    }
}


void add_big_numbers(mpz_t result, mpz_t op1, mpz_t op2) {
    if (DEBUG_MODE) { 
        printf("[INFO] - (add_big_numbers) Starting operation ...\n");
    }

    init_variable_for_big_numbers(result);
    mpz_add(result, op1, op2);

    if (DEBUG_MODE) { 
        printf("[INFO] - (free_variable_for_big_numbers) ");
        gmp_printf("Operation : %Zd + %Zd = %Zd\n", op1, op2, result);
    }
}