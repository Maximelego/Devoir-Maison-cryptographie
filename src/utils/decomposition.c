#include "include/decomposition.h"

void Decomp(const mpz_t n, mpz_t s, mpz_t d) {
    // Initialisation des variables.
    mpz_t temp;
    bn_init_var(temp);

    mpz_set_ui(s, 0);           // s = 0
    mpz_set(temp, n);           // temp  = n
    mpz_sub_ui(temp, temp, 1);  // temp = temp - 1

    // Calcul de s et d
    while (mpz_even_p(temp)) {          // while temp %2 == 0
        mpz_add_ui(s, s, 1);            //      s = s + 1
        mpz_divexact_ui(temp, temp, 2); //      temp = temp / 2
    }

    mpz_set(d, temp);           // d = temp
    bn_free_var(temp);
}


void ExpMod(const mpz_t n, const mpz_t a, const mpz_t t, mpz_t result) {

    





}


void print_decomp(const mpz_t n, const mpz_t s, const mpz_t d) {
    gmp_printf("[RESULT] - Decomposition of n = %Zd : \n", n);
    gmp_printf("         - s = %Zd\n", s);
    gmp_printf("         - d = %Zd\n", d);
    gmp_printf("Such as n - 1 = 2^s * d and with d odd.\n\n");
}


void log_decomp_to_file(const mpz_t n, const mpz_t s, const mpz_t d, FILE* file) {
    if (file != NULL) {
        gmp_fprintf(file, "- Decomposition of n = %Zd : \n", n);
        gmp_fprintf(file, " -> s = %Zd\n", s);
        gmp_fprintf(file, " -> d = %Zd\n\n", d);
        fflush(file);
    } else {
        printf("[ERROR] - Unable to open output file !\n");
    }
}