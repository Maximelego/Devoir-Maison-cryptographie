#include <stdio.h>
#include <stdlib.h>

#include "include/constants.h"
#include "utils/include/random_utils.h"


int main() {

    printf("# ---- Welcome ! ---- #\n\n");

    generate_big_randomNumber(150);

    printf("\n# ---- Goodbye ! ---- #\n\n");
    return 0;
}