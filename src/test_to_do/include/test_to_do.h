#ifndef TEST_TO_DO_H
#define TEST_TO_DO_H

#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

#include "include/constants.h"
#include "utils/include/random_utils.h"
#include "utils/include/decomposition.h"
#include "utils/include/miller_rabin_test.h"

void try_n_decomp(unsigned long n, gmp_randstate_t randstate, unsigned long* shared_iteration_count);
void try_n_exp_mod(unsigned long iterations, gmp_randstate_t randstate, unsigned long* shared_iteration_count);
void test_expmods(gmp_randstate_t randstate, unsigned long* shared_iteration_count);
void try_miller_rabin(gmp_randstate_t randstate, unsigned long* shared_iteration_count);
void test_eval(gmp_randstate_t randstate, unsigned long* shared_iteration_count);

#endif


