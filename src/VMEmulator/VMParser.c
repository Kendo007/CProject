//
// Created by cu001 on 5/9/24.
//

#include "VMParser.h"

#include <string.h>
#include <dirent.h>
#include <stdlib.h>
#include <sys/stat.h>

#include "VMCodeTranslator.h"

extern FILE* w;

int isDirectory(const char *path) {
    struct stat statusbuf;
    
    if (stat(path, &statusbuf) != 0)
        return 0;
    
    return S_ISDIR(statusbuf.st_mode);
}

void writeInit() {
    write("@256");
    write("D=A");
    write("@SP");
    write("M=D");

    const char* Command[] = {"call", "Sys.init", "0"};
    writeCall(Command);
}

void VMParser(const char *fileName) {
    initialiseBaseAddress();
    currFunction = malloc(sizeof(char) * 9);
    strcpy(currFunction, "Sys.init");
    currFunction[9] = '\0';

    if (isDirectory(fileName)) {
        DIR *dir;
        struct dirent *entry;

        const int fsize = strlen(fileName);
        char outputName[fsize + 5];
        snprintf(outputName, fsize + 5, "%s.asm", fileName);

        writeFile = fopen(outputName, "w+");

        writeInit();
        dir = opendir(fileName);
        if (dir == NULL) {
            printf("Error opening Directory: %s\n", fileName);
            exit(1);
        }

        while ((entry = readdir(dir)) != NULL)
        {
            if (entry->d_type == DT_REG) {
                if (strstr(entry->d_name, ".vm") != NULL) {
                    char outputFile[fsize + strlen(entry->d_name) + 2];
                    snprintf(outputFile, fsize + strlen(entry->d_name) + 2, "%s%c%s", fileName, kPathSeparator, entry->d_name);

                    VMCodeTranslator(outputFile);
                }
            }
        }

        closedir(dir);
        fclose(writeFile);
    } else {
        const int fsize = strlen(fileName);
        char outputName[fsize + 2];
        char temp[fsize];

        strncpy(temp, fileName, fsize - 3);
        temp[fsize - 3] = '\0';
        snprintf(outputName, fsize + 2, "%s.asm", temp);

        writeFile = fopen(outputName, "w+");
        VMCodeTranslator(fileName);

    }

    free(currFunction);
}
