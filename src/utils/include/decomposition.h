#ifndef DECOMPOSITION_H
#define DECOMPOSITION_H

#include <stdio.h>
#include <stdlib.h>

#include "gmp.h"
#include "include/constants.h" 

void Decomp(const mpz_t n, mpz_t s, mpz_t d);

void ExpMod(const mpz_t n, mpz_t a, mpz_t t, mpz_t result);
void ExpMod_GMP_style(const mpz_t mod, mpz_t base, mpz_t exponent, mpz_t result);

void print_decomp(const mpz_t n, const mpz_t a, const mpz_t d);
void log_decomp_to_file(const mpz_t n, const mpz_t s, const mpz_t d, FILE* file);
void log_expmod_to_file(const mpz_t result, const mpz_t n, const mpz_t a, const mpz_t t, FILE* file); 

#endif