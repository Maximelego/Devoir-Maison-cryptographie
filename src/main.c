#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <sys/wait.h>

#include "include/constants.h"
#include "utils/include/random_utils.h"
#include "utils/include/big_numbers_utils.h"
#include "utils/include/decomposition.h"

int end_flag = 0;

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
    // Variables initialization.
    unsigned long i = 0;
    FILE* file;
    mpz_t random_number; bn_init_var(random_number);
    mpz_t s;             bn_init_var(s);
    mpz_t d;             bn_init_var(d);

    if (LOG_TO_FILE) {
        file = fopen("output.txt", "w");
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
}

void try_n_exp_mod(const unsigned long n, gmp_randstate_t randstate) {
    
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

    printf("# ---- Welcome ! ---- #\n\n");

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
            // -> Long operation
            try_n_decomp(1000000, randstate);    

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
