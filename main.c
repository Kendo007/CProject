
#include <dirent.h>
#include <stdio.h>
#include <string.h>
#include <time.h>

#include "src/HackAssembler/HackAssembler.h"
#include "src/VMEmulator/VMEmulator.h"
#include "src/VMEmulator/VMParser.h"

int main(int argc, char * argv[]) {
    // clock_t start = clock();
    //
    // HackAssembler(argv[1]);
    //
    // clock_t stop = clock();
    // double elapsed = (double) (stop - start) / CLOCKS_PER_SEC;
    // printf("\nTime elapsed: %.2f milliseconds\n", elapsed * 1000);

    VMParser(argv[1]);

    return 0;
}

