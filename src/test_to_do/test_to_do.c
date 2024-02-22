#include "include/test_to_do.h"

void try_n_decomp(const unsigned long n, gmp_randstate_t randstate, unsigned long* shared_iteration_count) {

    if (DEBUG_MODE){ printf("[INFO] - Starting DECOMP tests...\n"); }

    // Variables initialization.
    unsigned long i = 0;
    FILE* file;
    mpz_t random_number, s, d, temp;

    mpz_inits(random_number, s, d, temp, NULL);

    if (LOG_TO_FILE) {
        file = fopen("output_decomp.txt", "w");
    }

    // Doing the N loop.
    while (i < n) {
        generate_big_randomNumber(RANDOM_NUMBERS_SIZE, randstate, random_number);
        Decomp(random_number, s, d);

        if (LOG_TO_FILE) { 
            log_decomp_to_file(random_number, s, d, file); 
        }

        i ++;
        *shared_iteration_count += 1;
    }

    // Freeing vars.
    mpz_clears(random_number, s, d, temp, NULL);

    if (LOG_TO_FILE) {
        fclose(file);
    }

    if (DEBUG_MODE){ printf("[INFO] - Done DECOMP tests.\n"); }  
}


void try_n_exp_mod(const unsigned long iterations, gmp_randstate_t randstate, unsigned long* shared_iteration_count, const int fast_mode) {

    if (DEBUG_MODE){ printf("[INFO] - Starting EXPMOD tests...\n"); }

    // Variables initialization.
    unsigned long i = 0;
    FILE* file;

    mpz_t a, n, t, result;
    mpz_inits(a, n, t, result, NULL);

    if (LOG_TO_FILE) {
        file = fopen("output_expmod.txt", "w");
    }

    // Doing the N loop.
    while (i < iterations) {

        generate_big_randomNumber(RANDOM_NUMBERS_SIZE, randstate, a);
        generate_big_randomNumber(RANDOM_NUMBERS_SIZE, randstate, n);
        generate_big_randomNumber(RANDOM_NUMBERS_SIZE, randstate, t);

        if (fast_mode) {
            ExpMod_GMP_style(n, a, t, result);
        } else {
            ExpMod(n, a, t, result);
        }

        if (LOG_TO_FILE) { 
            log_expmod_to_file(result, n, a, t, file); 
        }

        i ++;
        *shared_iteration_count += 1;
    }

    // Freeing vars.
    mpz_clears(a, n, t, result, NULL);

    if (LOG_TO_FILE) {
        fclose(file);
    }

    if (DEBUG_MODE){ printf("[INFO] - Done EXPMOD tests.\n"); }
}


void try_n_decomp_parallel(const unsigned long n, gmp_randstate_t randstate, unsigned long* shared_iteration_count) {
    if (DEBUG_MODE) {
        printf("[INFO] - Starting DECOMP tests...\n");
    }

    // Variables initialization.
    FILE* file;
    int max_threads = (ALLOCATED_CORES < 1) ? 1 : ALLOCATED_CORES;  // Adjust the threshold as needed

    if (LOG_TO_FILE) {
        file = fopen("output_decomp.txt", "w");
    }

    // Doing the N loop in parallel.
    #pragma omp parallel for num_threads(max_threads) schedule(dynamic)
    for (unsigned long i = 0; i < n; i++) {
        mpz_t local_random_number, local_s, local_d, local_temp;
        mpz_inits(local_random_number, local_s, local_d, local_temp, NULL);

        generate_big_randomNumber(RANDOM_NUMBERS_SIZE, randstate, local_random_number);
        Decomp(local_random_number, local_s, local_d);

        if (LOG_TO_FILE) {
            // Ensure that file writes are synchronized
            #pragma omp critical
            {
                log_decomp_to_file(local_random_number, local_s, local_d, file);
            }
        }

        mpz_clears(local_random_number, local_s, local_d, local_temp, NULL);

        // Ensure that shared counter is incremented in a thread-safe manner
        #pragma omp atomic
        *shared_iteration_count += 1;
    }
    if (LOG_TO_FILE) {
        fclose(file);
    }

    if (DEBUG_MODE) {
        printf("[INFO] - Done DECOMP tests.\n");
    }
}

void try_n_exp_mod_parallel(const unsigned long iterations, gmp_randstate_t randstate, unsigned long* shared_iteration_count, const int fast_mode) {
    if (DEBUG_MODE) {
        printf("[INFO] - Starting EXPMOD tests...\n");
    }

    // Variables initialization.
    FILE* file;
    int max_threads = (ALLOCATED_CORES < 1) ? 1 : ALLOCATED_CORES;  // Adjust the threshold as needed

    if (LOG_TO_FILE) {
        file = fopen("output_expmod.txt", "w");
    }

    // Doing the N loop in parallel.
    #pragma omp parallel for num_threads(max_threads) schedule(dynamic)
    for (unsigned long i = 0; i < iterations; i++) {
        mpz_t local_a, local_n, local_t, local_result;
        mpz_inits(local_a, local_n, local_t, local_result, NULL);

        generate_big_randomNumber(RANDOM_NUMBERS_SIZE, randstate, local_a);
        generate_big_randomNumber(RANDOM_NUMBERS_SIZE, randstate, local_n);
        generate_big_randomNumber(RANDOM_NUMBERS_SIZE, randstate, local_t);

        if (fast_mode) {
            ExpMod_GMP_style(local_n, local_a, local_t, local_result);
        } else {
            ExpMod(local_n, local_a, local_t, local_result);
        }

        if (LOG_TO_FILE) {
            // Ensure that file writes are synchronized
            #pragma omp critical
            {
                log_expmod_to_file(local_result, local_n, local_a, local_t, file);
            }
        }

        mpz_clears(local_a, local_n, local_t, local_result, NULL);

        // Ensure that shared counter is incremented in a thread-safe manner
        #pragma omp atomic
        *shared_iteration_count += 1;
    }

    if (LOG_TO_FILE) {
        fclose(file);
    }

    if (DEBUG_MODE) {
        printf("[INFO] - Done EXPMOD tests.\n");
    }
}


void test_expmods(gmp_randstate_t randstate, unsigned long* shared_iteration_count) {
    
    if (DEBUG_MODE){ printf("[INFO] - Starting the 2 EXPMOD tests...\n"); }

    // Variables initialization.
    FILE* file;
    mpz_t a, n, t, my_result, gmp_result;
    mpz_inits(a, n, t, my_result, gmp_result, NULL);

    generate_big_randomNumber(RANDOM_NUMBERS_SIZE, randstate, a);
    generate_big_randomNumber(RANDOM_NUMBERS_SIZE, randstate, n);
    generate_big_randomNumber(RANDOM_NUMBERS_SIZE, randstate, t);

    if (LOG_TO_FILE) {
        file = fopen("output_2expmod.txt", "w");
    }

    // We will try 3 expMods following 3 methods
    // My EXPMOD
    ExpMod(n, a, t, my_result);
    if (LOG_TO_FILE) { 
        fprintf(file, "My EXPMOD test :\n");
        fflush(file);
        log_expmod_to_file(my_result, n, a, t, file); 
    }
    *shared_iteration_count += 1;

    // The GMP EXPMOD
    ExpMod_GMP_style(n, a, t, gmp_result);
    if (LOG_TO_FILE) { 
        fprintf(file, "GMP EXPMOD test:\n");
        fflush(file);
        log_expmod_to_file(gmp_result, n, a, t, file); 
    }
    *shared_iteration_count += 1;

    // Checking result
    if(DEBUG_MODE){
        if(mpz_cmp(gmp_result, my_result) != 0){
            printf("[ERROR] - My Result is not the same as GMP !\n");
            fflush(stdout);
        } else {
            printf("[INFO] - My Result is the same as GMP !\n");
            fflush(stdout);
        }
    }
    *shared_iteration_count += 1;

    // Freeing vars.
    mpz_clears(a, n, t, my_result, gmp_result, NULL);

    if (LOG_TO_FILE) { fclose(file); }
    if (DEBUG_MODE)  { printf("[INFO] - Done the 2 EXPMOD tests.\n"); }
} 


void try_miller_rabin(gmp_randstate_t randstate, unsigned long* shared_iteration_count) {
    if (DEBUG_MODE){ printf("[INFO] - Starting the Miller Rabin tests...\n"); }

    // Variables initialization.
    FILE* file;
    mpz_t v1, v2, v3;
    mpz_init_set_str(v1, "FFFFFFFFFFFFFFFFC90FDAA22168C234C4C6628B80DC1CD129024E088A67CC74020BBEA63B139B22514A08798E3404DDEF9519B3CD3A431B302B0A6DF25F14374FE1356D6D51C245E485B576625E7EC6F44C42E9A63A3620FFFFFFFFFFFFFFFF", 16);
    mpz_init_set_str(v2, "FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFEC4FFFFFDAF0000000000000000000000000000000000000000000000000000000000000000000000000000000000000002D9AB", 16);
    mpz_init_set_str(v3, "FFFFFFFFFFFFFFFFC90FDAA22168C234C4C6628B80DC1CD129024E088A67CC74020BBEA63B139B22514A08798E3404DDEF9519B3CD3A431B302B0A6DF25F14374FE1356D6D51C245E485B576625E7EC6F44C42E9A637ED6B0BFF5CB6F406B7EDEE386BFB5A899FA5AE9F24117C4B1FE649286651ECE65381FFFFFFFFFFFFFFFF", 16);
    
    int v1_res;
    int v2_res;
    int v3_res;

    if (LOG_TO_FILE) { file = fopen("output_millerrabin.txt", "w"); }

    // Test on V1
    v1_res = MillerRabin(v1, randstate, MILLER_RABIN_ITERATIONS);
    *shared_iteration_count += 1;
    // Test on V2
    v2_res = MillerRabin(v2, randstate, MILLER_RABIN_ITERATIONS);
    *shared_iteration_count += 1;
    // Test on V3
    v3_res = MillerRabin(v3, randstate, MILLER_RABIN_ITERATIONS);
    *shared_iteration_count += 1;

    if (DEBUG_MODE) {
        printf("[INFO] - MillerRabin result for n1 : %i\n", v1_res);
        printf("[INFO] - MillerRabin result for n2 : %i\n", v2_res);
        printf("[INFO] - MillerRabin result for n3 : %i\n", v3_res);
    }

    if (LOG_TO_FILE) {
        fprintf(file, "MillerRabin result for n1 : %i\n", v1_res);
        fprintf(file, "MillerRabin result for n2 : %i\n", v2_res);
        fprintf(file, "MillerRabin result for n3 : %i\n", v3_res);
    }

    // Freeing vars.
    mpz_clears(v1, v2, v3, NULL);

    if (LOG_TO_FILE) { fclose(file); }
    if (DEBUG_MODE)  { printf("[INFO] - Done the Miller Rabin tests.\n"); }
} 



void test_eval(gmp_randstate_t randstate, unsigned long* shared_iteration_count, const int fast_mode) {

    if (DEBUG_MODE) { printf("[INFO] - Starting Eval tests...\n"); }

    FILE* file;
    int b = 128;
    int result;

    if (LOG_TO_FILE) { file = fopen("output_eval.txt", "w"); }

    while (b <= 4096) {

        for (int j = 0; j < 100; ++j) {
            result = Eval(randstate, MILLER_RABIN_ITERATIONS, b, fast_mode);

            if (LOG_TO_FILE) {
                fprintf(file, "Test for Eval : result = %i | b = %i\n", result, b);
                fflush(file);
            }
            *shared_iteration_count += 1;
        }

        if (LOG_TO_FILE) { fprintf(file, "\n\n"); }

        b *= 2;
    }

    if (LOG_TO_FILE) { fclose(file); }
    if (DEBUG_MODE)  { printf("[INFO] - Done Eval tests.\n"); }
}


void test_eval_parallel(gmp_randstate_t randstate, unsigned long* shared_iteration_count, const int fast_mode) {

    if (DEBUG_MODE) { printf("[INFO] - Starting Eval tests...\n"); }

    FILE* file;
    int b = 128;
    int result;

    if (LOG_TO_FILE) { file = fopen("output_eval.txt", "w"); }

    while (b <= 4096) {
        int max_threads = (ALLOCATED_CORES < 1) ? 1 : ALLOCATED_CORES;  // Adjust the threshold as needed

        // Use OpenMP to parallelize the inner loop with dynamic scheduling
        #pragma omp parallel for num_threads(max_threads) schedule(dynamic)
        for (int j = 0; j < 100; ++j) {
            int local_b;
            #pragma omp critical
            {
                local_b = b;
            }

            result = Eval(randstate, MILLER_RABIN_ITERATIONS, local_b, fast_mode);

            if (LOG_TO_FILE) {
                #pragma omp critical
                {
                    fprintf(file, "Test for Eval : result = %i | b = %i\n", result, local_b);
                    fflush(file);
                }
            }

            #pragma omp atomic
            *shared_iteration_count += 1;
        }

        if (LOG_TO_FILE) { fprintf(file, "\n\n"); }

        b *= 2;
    }

    if (LOG_TO_FILE) { fclose(file); }
    if (DEBUG_MODE)  { printf("[INFO] - Done Eval tests.\n"); }
}