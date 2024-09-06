//
// Created by cu001 on 5/9/24.
//

#include "VMCodeTranslator.h"

#include <stdbool.h>
#include <string.h>

#include "../../helper/hashmap.h"
#include "../../helper/myhashmap.h"
#include "../HackAssembler/AsssemblerFirstPass.h"

struct hashmap *baseAddress;
char* fileName;
bool wroteReturn = false;
bool wroteCall = false;
FILE* writeFile;

char kPathSeparator =
    #ifdef _WIN32
        '\\';
    #else
            '/';
    #endif

void write(const char* s) {
    fprintf(writeFile, s);
    fprintf(writeFile, "\n");
}

void parseCommand(char* command[], char* line) {
    int count = 0;
    const char* index = strstr(line, "//");

    if (index != NULL) {
        line[index - line] = '\0';
    }

    for (char *p = strtok(line," "); p != NULL, count < 3; p = strtok(NULL, " ")) {
        puts(p);
        command[count] = p;
        ++count;
    }
}

void translate(const char* Command[]) {

}


void VMCodeTranslator(char* filePath) {
    const int separatorIndex = strrchr(filePath, kPathSeparator) - filePath;
    const int dotIndex = strrchr(filePath, '.') - filePath;
    fileName = substring(separatorIndex, dotIndex, filePath);

    char * line = NULL;
    size_t len = 0;

    FILE* inputFile = fopen(filePath, "r");

    while (getline(&line, &len, inputFile) != -1) {
        char* Command[3];
        parseCommand(Command, line);
    }
}

void initialiseBaseAddress() {
    baseAddress = myhashmap_new();

    myhashmap_set(baseAddress, "argument", "@ARG");
    myhashmap_set(baseAddress, "local", "@LCL");
    myhashmap_set(baseAddress, "this", "@THIS");
    myhashmap_set(baseAddress, "that", "@THAT");
}