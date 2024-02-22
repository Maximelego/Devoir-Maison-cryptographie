#include "include/decomposition.h"

void Decomp(const mpz_t n, mpz_t s, mpz_t d) {
    // Initialisation des variables.
    mpz_t temp;     mpz_init(temp);

    mpz_set_ui(s, 0);           // s = 0
    mpz_set(temp, n);           // temp = n
    mpz_sub_ui(temp, temp, 1);  // temp = temp - 1

    // Calcul de s et d
    while (mpz_even_p(temp) == 0) {     // while temp %2 == 0
        mpz_add_ui(s, s, 1);            //      s = s + 1
        mpz_div_ui(temp, temp, 2);      //      temp = temp / 2
    }

    mpz_set(d, temp);           // d = temp
    mpz_clear(temp);
}


void ExpMod(const mpz_t mod, mpz_t base, mpz_t exponent, mpz_t result) {
    // Base case: if exponent is 0, return 1
    if (mpz_cmp_ui(exponent, 0) == 0) {
        mpz_set_ui(result, 1);
        return;
    }
    // Base case: if exponent is 1, return base % mod
    if (mpz_cmp_ui(exponent, 1) == 0) {
        mpz_mod(result, base, mod);
        return;
    }

    mpz_t temp_result, new_exponent, new_base;
    mpz_inits(temp_result, new_exponent, new_base, NULL);
    
    mpz_mul(new_base, base, base); // new_base = base * base
    mpz_mod(new_base, new_base, mod); // new_base = new_base % mod

    // If exponent is even, do (base^2)^(exponent/2)
    if (mpz_even_p(exponent) != 0) {
        
        mpz_fdiv_q_2exp(new_exponent, exponent, 1); // new_exponent = exponent / 2
        ExpMod(mod, new_base, new_exponent, temp_result);

    } else { // If exponent is odd, do base * (base^2)^((exponent-1)/2)

        mpz_sub_ui(new_exponent, exponent, 1); // new_exponent = exponent - 1
        mpz_fdiv_q_2exp(new_exponent, new_exponent, 1); // new_exponent = new_exponent / 2

        ExpMod(mod, new_base, new_exponent, temp_result);

        mpz_mul(temp_result, temp_result, base); // temp_result = temp_result * base
        mpz_mod(temp_result, temp_result, mod); // temp_result = temp_result % mod

    }

    mpz_set(result, temp_result);
    mpz_clears(new_exponent, new_base, temp_result, NULL);
}


void ExpMod_GMP_style(const mpz_t mod, mpz_t base, mpz_t exponent, mpz_t result) {
    mpz_powm(result, base, exponent, mod);
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
