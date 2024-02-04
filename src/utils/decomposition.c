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


void ExpMod(const mpz_t mod, mpz_t base, mpz_t exponent, mpz_t result) {
    // mpz_t base_squared;     mpz_init(base_squared);
    // mpz_t t_divided;        mpz_init(t_divided);

    // // Initialisation du résultat à 1
    // if (mpz_cmp_ui(exponent, 0) == 0) {
    //     mpz_set_ui(result, 1);
    //     return;
    // }

    // if (mpz_cmp_ui(exponent, 1)) {      // If t == 1;
    //     mpz_mod(result, base, mod);     // -> result = base % mod
    // } else {
    //     mpz_mul(base_squared, base, base);      // base = base²

    //     if (mpz_even_p(exponent)) {             // If t % 2 == 0
    //         mpz_div_ui(t_divided, exponent, 2); // -> t = t/2
    //         ExpMod(mod, base_squared, t_divided, result);
    //         mpz_mod(result, result, mod);

    //     } else if (!mpz_even_p(exponent)) {

    //         mpz_sub_ui(t_divided, t_divided, 1);    // -> t = t - 1
    //         mpz_div_ui(t_divided, exponent, 2);     // -> t = t/2
    //         ExpMod(mod, base_squared, t_divided, result);
    //         mpz_mul(result, base, result);         // -> result = base * result
    //         mpz_mod(result, result, mod);           // -> result = result % mod
    //     } 
    // } 

    // bn_free_var(base_squared);
    // bn_free_var(t_divided);


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

    mpz_t temp_result;      mpz_init(temp_result);

    mpz_t new_exponent;     mpz_init(new_exponent);
    mpz_t new_base;         mpz_init(new_base);
    
    // If exponent is even, do (base^2)^(exponent/2)
    if (mpz_even_p(exponent) != 0) {

        mpz_fdiv_q_2exp(new_exponent, exponent, 1); // new_exponent = exponent / 2
        mpz_mul(new_base, base, base); // new_base = base * base
        mpz_mod(new_base, new_base, mod); // new_base = new_base % mod

        ExpMod(mod, new_base, new_exponent, temp_result);

        mpz_clear(new_exponent);
        mpz_clear(new_base);

    } else { // If exponent is odd, do base * (base^2)^((exponent-1)/2)

        mpz_sub_ui(new_exponent, exponent, 1); // new_exponent = exponent - 1
        mpz_fdiv_q_2exp(new_exponent, new_exponent, 1); // new_exponent = new_exponent / 2
        mpz_mul(new_base, base, base); // new_base = base * base
        mpz_mod(new_base, new_base, mod); // new_base = new_base % mod
        
        ExpMod(mod, new_base, new_exponent, temp_result);

        mpz_mul(temp_result, temp_result, base); // temp_result = temp_result * base
        mpz_mod(temp_result, temp_result, mod); // temp_result = temp_result % mod
        mpz_clear(new_exponent);
        mpz_clear(new_base);
    }
    // Set the result
    mpz_set(result, temp_result);
    mpz_clear(temp_result);
}


void ExpMod_ChatGPT_style(const mpz_t mod, mpz_t base, mpz_t exponent, mpz_t result) {
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
