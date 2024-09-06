
#include <stdio.h>
#include <time.h>

#include "src/HackAssembler/HackAssembler.h"

int main(int argc, char * argv[]) {
    clock_t start = clock();

    HackAssembler(argv[1]);

    clock_t stop = clock();
    double elapsed = (double) (stop - start) / CLOCKS_PER_SEC;
    printf("\nTime elapsed: %.2f milliseconds", elapsed * 1000);

    return 0;
}

