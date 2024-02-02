#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <sys/wait.h>

#include "include/constants.h"
#include "utils/include/random_utils.h"
#include "utils/include/big_numbers_utils.h"
#include "utils/include/decomposition.h"

int end_flag = 0;       // Flag for ending the loading animation.

void sigusr1_handler(int signo) {
    if (signo == SIGUSR1) {
        end_flag = 1;
    }
}


void init_randstate(gmp_randstate_t randstate) {
    gmp_randinit_default(randstate);
    gmp_randseed_ui(randstate, RANDOM_SEED);
}


void try_n_decomp(const unsigned long n, gmp_randstate_t randstate) {

    if (DEBUG_MODE){ printf("[INFO] - Starting DECOMP tests...\n"); }

    // Variables initialization.
    unsigned long i = 0;
    FILE* file;
    mpz_t random_number; bn_init_var(random_number);
    mpz_t s;             bn_init_var(s);
    mpz_t d;             bn_init_var(d);

    if (LOG_TO_FILE) {
        file = fopen("output_decomp.txt", "w");
    }

    // Doing the N loop.
    while (i < n) {
        generate_big_randomNumber(RANDOM_NUMBERS_SIZE, randstate, random_number);
        Decomp(random_number, s, d);
        // print_decomp(random_number, s, d);

        if (LOG_TO_FILE) { 
            log_decomp_to_file(random_number, s, d, file); 
        }

        i ++;
    }

    // Freeing vars.
    bn_free_var(random_number);
    bn_free_var(s);
    bn_free_var(d);

    if (LOG_TO_FILE) {
        fclose(file);
    }

    if (DEBUG_MODE){ printf("[INFO] - Done DECOMP tests.\n"); }  
}


void try_n_exp_mod(const unsigned long iterations, gmp_randstate_t randstate) {

    if (DEBUG_MODE){ printf("[INFO] - Starting EXPMOD tests...\n"); }

    // Variables initialization.
    unsigned long i = 0;
    FILE* file;
    mpz_t a;        bn_init_var(a);
    mpz_t n;        bn_init_var(n);
    mpz_t t;        bn_init_var(t);
    mpz_t result;   bn_init_var(result);

    if (LOG_TO_FILE) {
        file = fopen("output_expmod.txt", "w");
    }

    // Doing the N loop.
    while (i < iterations) {

        generate_big_randomNumber(RANDOM_NUMBERS_SIZE, randstate, a);
        generate_big_randomNumber(RANDOM_NUMBERS_SIZE, randstate, n);
        generate_big_randomNumber(RANDOM_NUMBERS_SIZE, randstate, t);

        ExpMod(n, a, t, result);        // TODO : FIX THIS !!!! Too slow, waaaay too slooooow

        if (LOG_TO_FILE) { 
            log_expmod_to_file(result, n, a, t, file); 
        }

        i ++;
    }

    // Freeing vars.
    bn_free_var(result);
    bn_free_var(a);
    bn_free_var(n);
    bn_free_var(t);

    if (LOG_TO_FILE) {
        fclose(file);
    }

    if (DEBUG_MODE){ printf("[INFO] - Done EXPMOD tests.\n"); }
}



void loadingAnimation() {

    const char* animationStrings[] = {".  ", ".. ", "...", "   "};
    const int numStrings = sizeof(animationStrings) / sizeof(animationStrings[0]);
    const int delayMicroseconds = 500000;  // Délai d'attente entre les états (microsecondes)

    printf("[INFO] - Computing \n");

    while (!end_flag) {
        for (int i = 0; i < numStrings; ++i) {
            printf("%s\r", animationStrings[i]);  // Utilise \r pour revenir au début de la ligne
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

    struct sigaction prepaSignal;
    prepaSignal.sa_handler=&sigusr1_handler;
    prepaSignal.sa_flags=0;
    sigemptyset(&prepaSignal.sa_mask);
    sigaction(SIGUSR1, &prepaSignal, 0);
    
    switch(child_pid = fork()) {
        case 0 :
            // Child process.
            // -> Long operation(s)
            try_n_decomp(ITERATION_NUMBER, randstate);
            try_n_exp_mod(ITERATION_NUMBER, randstate);

            if (DEBUG_MODE){
                printf("[INFO] - All tests are done ! Exiting child process...\n");
                fflush(stdout);
            }  

            // -> When done, we signal it to the parent process.
            kill(getppid(), SIGUSR1);
            exit(EXIT_SUCCESS);
        case -1: 
            perror("[ERROR] - Error while creating child.");
            return EXIT_FAILURE;

        default:
            // Code du processus père (animation)
            loadingAnimation();

            // Attente de la fin du processus fils
            int status;
            waitpid(child_pid, &status, 0);

            printf("\n\n# ---- Goodbye ! ---- #\n\n");
            return EXIT_SUCCESS;
    }
}
