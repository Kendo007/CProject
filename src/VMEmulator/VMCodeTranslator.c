//
// Created by cu001 on 5/9/24.
//

#include "VMCodeTranslator.h"

#include <stdbool.h>

#include "../../helper/hashmap.h"
#include "../../helper/myhashmap.h"

struct hashmap *baseAddress;

bool wroteReturn = false;
bool wroteCall = false;
FILE* writeFile;

char kPathSeparator =
    #ifdef _WIN32
        '\\';
    #else
            '/';
    #endif

void VMCodeTranslator(const char* fileName) {

}

void initialiseBaseAddress() {
    baseAddress = myhashmap_new();

    myhashmap_set(baseAddress, "argument", "@ARG");
    myhashmap_set(baseAddress, "local", "@LCL");
    myhashmap_set(baseAddress, "this", "@THIS");
    myhashmap_set(baseAddress, "that", "@THAT");
}