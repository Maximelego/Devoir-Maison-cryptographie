#include "include/big_numbers_utils.h"


mpz_t* init_variable_for_big_numbers() {

    if (DEBUG_MODE) { 
        printf("[INFO] - (init_variable_for_big_numbers) Preparing var ...\n");
    }
    
    mpz_t var;
    mpz_init(var);

    if (DEBUG_MODE) { 
        printf("[INFO] - (init_variable_for_big_numbers) Done !\n");
    }

    return &var;
}


void free_variable_for_big_numbers(mpz_t* var) {
    if (DEBUG_MODE) { 
        printf("[INFO] - (free_variable_for_big_numbers) Freeing var ...\n");
    }

    mpz_clear(*var);

    if (DEBUG_MODE) { 
        printf("[INFO] - (free_variable_for_big_numbers) Done !\n");
    }
}