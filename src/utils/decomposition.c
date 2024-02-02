#include "include/decomposition.h"

void Decomp(const mpz_t n, mpz_t s, mpz_t d) {
    // Initialisation des variables.
    mpz_t temp;     bn_init_var(temp);

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


void ExpMod(const mpz_t mod, mpz_t base, mpz_t exponent,  mpz_t result) {
    mpz_t tmp;
    mpz_init(tmp);

    // Initialisation du résultat à 1
    mpz_set_ui(result, 1);

    // Copie de l'exposant dans une variable temporaire
    mpz_set(tmp, exponent);

    while (mpz_cmp_ui(tmp, 0) > 0) {
        // Si l'exposant est impair
        if (mpz_odd_p(tmp)) {
            mpz_mul(result, result, base);
            mpz_mod(result, result, mod);
        }

        // Division de l'exposant par 2
        mpz_div_ui(tmp, tmp, 2);

        // Calcul du carré de la base modulo mod
        mpz_mul(base, base, base);
        mpz_mod(base, base, mod);
    }

    mpz_clear(tmp);
}

void print_decomp(const mpz_t n, const mpz_t s, const mpz_t d) {
    gmp_printf("[RESULT] - Decomposition of n = %Zd : \n", n);
    gmp_printf("         - s = %Zd\n", s);
    gmp_printf("         - d = %Zd\n", d);
    gmp_printf("Such as n - 1 = 2^s * d and with d odd.\n\n");
}


void print_expmod(const mpz_t result, const mpz_t n, const mpz_t a, const mpz_t t) {
    gmp_printf("[RESULT] - ExpMod of : \n");
    gmp_printf(" -> a      = %Zd\n", a);
    gmp_printf(" -> t      = %Zd\n", t);
    gmp_printf(" -> n      = %Zd\n", n);
    gmp_printf(" -> result = %Zd\n\n", result);
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