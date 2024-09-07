
#include <stdio.h>
#include <string.h>
#include <time.h>

#include "src/HackAssembler/HackAssembler.h"
#include "src/VMEmulator/VMParser.h"

int main(int argc, char * argv[]) {
    clock_t start = clock();

    if (strcmp(argv[2], "1") == 0) {
        HackAssembler(argv[1]);
    } else if (strcmp(argv[2], "2") == 0) {
        VMParser(argv[1]);
    }

    clock_t stop = clock();
    double elapsed = (double) (stop - start) / CLOCKS_PER_SEC;
    printf("\nTime elapsed: %.2f milliseconds\n", elapsed * 1000);

    return 0;
}

