#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <unistd.h>
#include <errno.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/mman.h>

#include "include/constants.h"
#include "utils/include/random_utils.h"
#include "utils/include/decomposition.h"
#include "utils/include/miller_rabin_test.h"


int end_flag = 0;       // Flag for ending the loading animation.
int total_test_iter = (2 * ITERATION_NUMBER) + 2 + 3 ;


void sigusr1_handler(int signo) {
    if (signo == SIGUSR1) {
        end_flag = 1;
    }
}


void init_randstate(gmp_randstate_t randstate) {
    gmp_randinit_default(randstate);
    gmp_randseed_ui(randstate, RANDOM_SEED);
}


void try_n_decomp(const unsigned long n, gmp_randstate_t randstate, unsigned long* shared_iteration_count) {

    if (DEBUG_MODE){ printf("[INFO] - Starting DECOMP tests...\n"); }

    // Variables initialization.
    unsigned long i = 0;
    FILE* file;
    mpz_t random_number; mpz_init(random_number);
    mpz_t s;             mpz_init(s);
    mpz_t d;             mpz_init(d);
    mpz_t temp;          mpz_init(temp);

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
    mpz_clear(random_number);
    mpz_clear(s);
    mpz_clear(d);
    mpz_clear(temp);

    if (LOG_TO_FILE) {
        fclose(file);
    }

    if (DEBUG_MODE){ printf("[INFO] - Done DECOMP tests.\n"); }  
}


void try_n_exp_mod(const unsigned long iterations, gmp_randstate_t randstate, unsigned long* shared_iteration_count) {

    if (DEBUG_MODE){ printf("[INFO] - Starting EXPMOD tests...\n"); }

    // Variables initialization.
    unsigned long i = 0;
    FILE* file;
    mpz_t a;        mpz_init(a);
    mpz_t n;        mpz_init(n);
    mpz_t t;        mpz_init(t);
    mpz_t result;   mpz_init(result);

    if (LOG_TO_FILE) {
        file = fopen("output_expmod.txt", "w");
    }

    // Doing the N loop.
    while (i < iterations) {

        generate_big_randomNumber(RANDOM_NUMBERS_SIZE, randstate, a);
        generate_big_randomNumber(RANDOM_NUMBERS_SIZE, randstate, n);
        generate_big_randomNumber(RANDOM_NUMBERS_SIZE, randstate, t);

        ExpMod(n, a, t, result);

        if (LOG_TO_FILE) { 
            log_expmod_to_file(result, n, a, t, file); 
        }

        i ++;
        *shared_iteration_count += 1;
    }

    // Freeing vars.
    mpz_clear(result);
    mpz_clear(a);
    mpz_clear(n);
    mpz_clear(t);

    if (LOG_TO_FILE) {
        fclose(file);
    }

    if (DEBUG_MODE){ printf("[INFO] - Done EXPMOD tests.\n"); }
}


void test_expmods(gmp_randstate_t randstate, unsigned long* shared_iteration_count) {
    
    if (DEBUG_MODE){ printf("[INFO] - Starting the 3 EXPMOD tests...\n"); }

    // Variables initialization.
    FILE* file;
    mpz_t a;            mpz_init(a);
    mpz_t n;            mpz_init(n);
    mpz_t t;            mpz_init(t);
    mpz_t my_result;    mpz_init(my_result);
    mpz_t gmp_result;   mpz_init(gmp_result);

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

    if(DEBUG_MODE){
        if(!(mpz_cmp(gmp_result, my_result) == 0)){
            printf("[ERROR] - My Result is not the same as GMP !\n");
            fflush(stdout);
        } else {
            printf("[INFO] - My Result is the same as GMP !\n");
            fflush(stdout);
        }
    } 
    
    // Freeing vars.
    mpz_clear(my_result);
    mpz_clear(gmp_result);
    mpz_clear(a);
    mpz_clear(n);
    mpz_clear(t);

    if (LOG_TO_FILE) { fclose(file); }
    if (DEBUG_MODE)  { printf("[INFO] - Done the 3 EXPMOD tests.\n"); }
} 


void try_miller_rabin(gmp_randstate_t randstate, unsigned long* shared_iteration_count ) {
    if (DEBUG_MODE){ printf("[INFO] - Starting the Miller Rabin tests...\n"); }

    // Variables initialization.
    FILE* file;
    mpz_t v1;            mpz_init_set_str(v1, "FFFFFFFFFFFFFFFFC90FDAA22168C234C4C6628B80DC1CD129024E088A67CC74020BBEA63B139B22514A08798E3404DDEF9519B3CD3A431B302B0A6DF25F14374FE1356D6D51C245E485B576625E7EC6F44C42E9A63A3620FFFFFFFFFFFFFFFF", 16);
    mpz_t v2;            mpz_init_set_str(v2, "FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFEC4FFFFFDAF0000000000000000000000000000000000000000000000000000000000000000000000000000000000000002D9AB", 16);
    mpz_t v3;            mpz_init_set_str(v3, "FFFFFFFFFFFFFFFFC90FDAA22168C234C4C6628B80DC1CD129024E088A67CC74020BBEA63B139B22514A08798E3404DDEF9519B3CD3A431B302B0A6DF25F14374FE1356D6D51C245E485B576625E7EC6F44C42E9A637ED6B0BFF5CB6F406B7EDEE386BFB5A899FA5AE9F24117C4B1FE649286651ECE65381FFFFFFFFFFFFFFFF", 16);
    int v1_res = 0;
    int v2_res = 0;
    int v3_res = 0;

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

    v1_res = mpz_probab_prime_p(v1, MILLER_RABIN_ITERATIONS);
    v2_res = mpz_probab_prime_p(v2, MILLER_RABIN_ITERATIONS);
    v3_res = mpz_probab_prime_p(v3, MILLER_RABIN_ITERATIONS);

    if (DEBUG_MODE) {
        printf("[INFO] - MillerRabin result for n1 should be : %i\n", v1_res);
        printf("[INFO] - MillerRabin result for n2 should be : %i\n", v2_res);
        printf("[INFO] - MillerRabin result for n3 should be : %i\n", v3_res);
    }

    if (LOG_TO_FILE) {
        fprintf(file, "MillerRabin result for n1 : %i\n", v1_res);
        fprintf(file, "MillerRabin result for n2 : %i\n", v2_res);
        fprintf(file, "MillerRabin result for n3 : %i\n", v3_res);
    }

    // Freeing vars.
    mpz_clear(v1);
    mpz_clear(v2);
    mpz_clear(v3);

    if (LOG_TO_FILE) { fclose(file); }
    if (DEBUG_MODE)  { printf("[INFO] - Done the Miller Rabin tests.\n"); }
} 




void loadingAnimation(unsigned long* shared_iteration_count) {

    const char* animationStrings[] = {".  ", ".. ", "...", "   "};
    const int numStrings = sizeof(animationStrings) / sizeof(animationStrings[0]);
    const int delayMicroseconds = 500000;  // Délai d'attente entre les états (microsecondes)
    unsigned long overall_progress = 0;

    printf("[INFO] - Computing \n");

    while (!end_flag) {
        for (int i = 0; i < numStrings; ++i) {
            overall_progress = (*shared_iteration_count * 100) / total_test_iter;
            printf("%s  %li%% \r", animationStrings[i], overall_progress);  // Utilise \r pour revenir au début de la ligne
            fflush(stdout);
            usleep(delayMicroseconds);
        }
    }
}



int main() {

    printf("\n\n# ---- Welcome ! ---- #\n\n\n");

    if (LOG_TO_FILE) { printf("[INFO] - LOG_TO_FILE is set to true. Results will be outputted into an output.txt file.\n"); }
    if (DEBUG_MODE)  { printf("[INFO] - DEBUG_MODE is set to true. Progress of tests will be displayed on standard output.\n"); }

    gmp_randstate_t randstate; 
    init_randstate(randstate);

    pid_t child_pid;

    // Shared memory segment.
    unsigned long *p;
    // Create a shared memory segment
    int shm_fd = shm_open("/my_shared_memory", O_CREAT | O_RDWR, 0666);
    ftruncate(shm_fd, sizeof(unsigned long));

    // Map the shared memory segment into the address space
    p = (unsigned long *)mmap(NULL, sizeof(unsigned long), PROT_READ | PROT_WRITE, MAP_SHARED, shm_fd, 0);    printf("[INFO] - All tests are done ! Exiting child process...1\n");
    *p = 0;

    struct sigaction prepaSignal;
    prepaSignal.sa_handler = &sigusr1_handler;
    prepaSignal.sa_flags=0;
    sigemptyset(&prepaSignal.sa_mask);
    sigaction(SIGUSR1, &prepaSignal, 0);


    switch(child_pid = fork()) {
        case 0 :
            // Child process.
            // -> Long operation(s)
            try_n_decomp(ITERATION_NUMBER, randstate, p);
            try_n_exp_mod(ITERATION_NUMBER, randstate, p);
            test_expmods(randstate, p);
            try_miller_rabin(randstate, p);

            if (DEBUG_MODE){
                printf("[INFO] - All tests are done ! Exiting child process...\n");
                fflush(stdout);
            }  

            // -> When done, we signal it to the parent process.
            munmap(p, sizeof(unsigned long));
            kill(getppid(), SIGUSR1);
            exit(EXIT_SUCCESS);
        case -1: 
            perror("[ERROR] - Error while creating child.");
            return EXIT_FAILURE;

        default:
            // Code du processus père (animation)
            loadingAnimation(p);

            // Attente de la fin du processus fils
            int status;
            waitpid(child_pid, &status, 0);

            // Detach and unlink the shared memory
            munmap(p, sizeof(unsigned long));
            shm_unlink("/my_shared_memory");

            printf("\n\n# ---- Goodbye ! ---- #\n\n");
            return EXIT_SUCCESS;
    }
}
