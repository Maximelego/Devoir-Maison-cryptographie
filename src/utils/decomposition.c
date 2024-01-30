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


void exponential(mpz_t a, mpz_t t, mpz_t result) {
    if (mpz_cmp_ui(t, 1)) {         // If t is 1.
        mpz_set(result, a);             // result = a
    } else if(mpz_even_p(t)) {      // If t is pair.
        mpz_pow_ui(a, a, 2);            // a = a²
        mpz_divexact_ui(t, t, 2);       // t = t/2
        exponential(a, t, result);      // exponential(a², t/2, result)
    } else {                        // If t > 2 and odd
        mpz_pow_ui(a, a, 2);            // a = a²
        mpz_sub_ui(t, t, 1);            // t = t - 1
        mpz_divexact_ui(t, t, 2);       // t = t/2
        exponential(a, t, result);      // exponential(a², (t-1)/2, result)
        mpz_mul(result, result, a);     // result = a * result
    }
}


void ExpMod(const mpz_t n, mpz_t a, mpz_t t, mpz_t result) {
    mpz_t temp; bn_init_var(temp);

    exponential(a, t, temp);        // temp = a^t
    mpz_mod(result, temp, n);       // result = temp mod(n)

    bn_free_var(temp);
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
        printf("[ERROR] - Unable to open output decomp file !\n");
    }
}

void log_expmod_to_file(const mpz_t result, const mpz_t n, const mpz_t a, const mpz_t t, FILE* file) {
    if (file != NULL) {
        gmp_fprintf(file, "- ExpMod of : \n");
        gmp_fprintf(file, " -> a      = %Zd\n", a);
        gmp_fprintf(file, " -> t      = %Zd\n", t);
        gmp_fprintf(file, " -> n      = %Zd\n", n);
        gmp_fprintf(file, " -> result = %Zd\n\n", result);
        fflush(file);
    } else {
        printf("[ERROR] - Unable to open output expmod file !\n");
    }
}