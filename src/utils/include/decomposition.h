#ifndef DECOMPOSITION_H
#define DECOMPOSITION_H

#include <stdio.h>
#include <stdlib.h>

#include "gmp.h"
#include "include/constants.h" 
#include "big_numbers_utils.h"

void Decomp(const mpz_t n, mpz_t s, mpz_t d);
void ExpMod(const mpz_t n, const mpz_t a, const mpz_t t, mpz_t result);
void print_decomp(const mpz_t n, const mpz_t a, const mpz_t d);
void log_decomp_to_file(const mpz_t n, const mpz_t s, const mpz_t d, FILE* file);

#endif