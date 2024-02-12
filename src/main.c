#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <fcntl.h>
#include <sys/wait.h>
#include <sys/mman.h>
#include <sys/time.h>

#include "include/constants.h"
#include "utils/include/random_utils.h"
#include "test_to_do/include/test_to_do.h"


int end_flag = 0;       // Flag for ending the loading animation.
int total_test_iter = (2 * ITERATION_NUMBER) + 2 + 3 + (100 * 6);


void sigusr1_handler(int signo) {
    if (signo == SIGUSR1) {
        end_flag = 1;
    }
}

void init_randstate(gmp_randstate_t randstate) {
    gmp_randinit_default(randstate);
    gmp_randseed_ui(randstate, RANDOM_SEED);
}

void loadingAnimation(const unsigned long* shared_iteration_count) {

    const char* animationStrings[] = {".  ", "..  ", "... ", "....", "    "};
    const int numStrings = sizeof(animationStrings) / sizeof(animationStrings[0]);
    const int delayMicroseconds = 200000;  // Délai d'attente entre les états (microsecondes)
    float overall_progress;

    printf("[INFO] - Computing \n");

    while (!end_flag) {
        for (int i = 0; i < numStrings; ++i) {
            overall_progress = (float) (*shared_iteration_count * 100) / (float) total_test_iter;
            printf("[PROGRESS] - %.3f%%   %s\r", overall_progress, animationStrings[i]);  // Utilise \r pour revenir au début de la ligne
            fflush(stdout);
            usleep(delayMicroseconds);
        }
    }
}

void run_all_tests(gmp_randstate_t randstate, unsigned long* p) {

    // Tests for N Decomp() method calls.
    try_n_decomp(ITERATION_NUMBER, randstate, p);

    // Tests for N ExpMod() method calls.
    try_n_exp_mod(ITERATION_NUMBER, randstate, p);

    // Test to check that ExpMod returns the result it should return.
    test_expmods(randstate, p);

    // Test for the 3 values for the Prime nmber test of Miller Rabin
    try_miller_rabin(randstate, p);

    // Test for the 600 iterations of the Eval() method.
    test_eval(randstate, p);
    
}


int main() {

    printf("\n\n# ---- Welcome ! ---- #\n\n\n");

    struct timeval t1, t2;
    double elapsedTime;

    if (DEBUG_MODE) {
        // Start timer
        gettimeofday(&t1, NULL);
    }

    if (LOG_TO_FILE) { printf("[INFO] - LOG_TO_FILE is set to true. Results will be outputted into an output.txt file.\n"); }
    if (DEBUG_MODE)  { printf("[INFO] - DEBUG_MODE is set to true. Progress of tests will be displayed on standard output.\n"); }

    gmp_randstate_t randstate; 
    init_randstate(randstate);

    pid_t child_pid;

    // Shared memory segment.
    unsigned long *p;
    // Create a shared memory segment
    int shm_fd = shm_open("/my_shared_memory", O_CREAT | O_RDWR, 0666);
    int t = ftruncate(shm_fd, sizeof(unsigned long));

    // Map the shared memory segment into the address space
    p = (unsigned long *)mmap(NULL, sizeof(unsigned long), PROT_READ | PROT_WRITE, MAP_SHARED, shm_fd, 0);
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
            run_all_tests(randstate, p);

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


            if (DEBUG_MODE) {
                // Stop timer
                gettimeofday(&t2, NULL);

                // Compute and print the elapsed time in
                elapsedTime = (double) (t2.tv_sec - t1.tv_sec);
                printf("[INFO] - Time elapsed : %li min : %2ld s.\n", (long) elapsedTime/60 , (long) elapsedTime % 60);
            }

            printf("\n\n# ---- Goodbye ! ---- #\n\n");
            return EXIT_SUCCESS;
    }
}
