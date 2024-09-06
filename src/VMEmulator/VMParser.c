//
// Created by cu001 on 5/9/24.
//

#include "VMParser.h"

#include <string.h>
#include <sys/stat.h>

#include "VMCodeTranslator.h"

extern FILE* w;


int isDirectory(const char *path) {
    struct stat statusbuf;
    
    if (stat(path, &statusbuf) != 0)
        return 0;
    
    return S_ISDIR(statusbuf.st_mode);
}

void VMParser(const char *fileName) {
    if (isDirectory(fileName)) {
        int fsize = strlen(fileName);
        char outputName[fsize + 5];
        snprintf(outputName, fsize + 5, "%s.asm", fileName);

        w = fopen(outputName, "w+");
    } else {

    }
}