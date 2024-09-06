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
int boolCount = 0;
int callCount = 0;
char* fileName;
int fileNameLength;
bool wroteReturn = false;
bool wroteCall = false;
char* currFunction = "Sys.init";
int currFunctionLength = strlen(currFunction);
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

void getBaseAddress(const char* Command[]) {
    const char* temp = myhashmap_get(baseAddress, Command[1]);

    if (temp != NULL) {
        write(temp);
        write("D=M");
    } else if (strcmp(Command[1], "temp") == 0) {
        write("@5");
    } else if (strcmp(Command[1], "pointer") == 0) {
        write("@3");
    }

    write("D=A");
}

void pop(const char* Command[]) {
    const int c2 = strlen(Command[2]);

    if (strcmp(Command[1], "static") == 0) {
        write("@SP");
        write("AM=M-1");
        write("D=M");
        char temp[3 + fileNameLength + c2];
        snprintf(temp, 3 + fileNameLength + c2, "@%s.%s", fileName, Command[2]);

        write(temp);
        write("M=D");

        return;
    }

    getBaseAddress(Command);

    char temp[2 + c2];
    snprintf(temp, 2 + c2, "@%s", Command[2]);
    write(temp);
    write("D=D+A");
    write("@SP");
    write("AM=M-1");
    write("D=D+M");    // D = addr + val
    write("A=D-M");    // A = addr + val - val
    write("M=D-A");    // RAM[addr] = addr + val - addr
}

void push(const char* Command[]) {
    int c2 = strlen(Command[2]);

    if (strcmp(Command[1], "constant") == 0) {
        char temp[2 + c2];
        snprintf(temp, 2 + c2, "@%s", Command[2]);

        write(temp);
        write("D=A");
    } else if (strcmp(Command[1], "static") == 0) {
        char temp[3 + fileNameLength + c2];
        snprintf(temp, 3 + fileNameLength + c2, "@%s.%s", fileName, Command[2]);

        write(temp);
        write("D=M");
    } else {
        getBaseAddress(Command);

        char temp[2 + c2];
        snprintf(temp, 2 + c2, "@%s", Command[2]);

        write(temp);
        write("A=D+A");
        write("D=M");
    }

    write("@SP");
    write("M=M+1");
    write("A=M-1");
    write("M=D");
}

bool memoryCommand(const char* Command[]) {
    if (Command[0] == NULL)
        return false;

    if (strcmp(Command[0], "push") == 0)
        push(Command);
    else if (strcmp(Command[0], "pop") == 0)
        pop(Command);
    else
        return false;

    return true;
}

void booleanPush(const char* jumpCondition) {
    write("D=M-D");

    write("@SP");
    write("A=M-1");
    write("M=-1");
    write("@CONT" + boolCount);
    fprintf(writeFile, "D;");
    write(jumpCondition);

    write("@SP");
    write("A=M-1");
    write("M=0");

    char temp[11]
    snprintf(temp, 11, "(CONT%d)", boolCount);
    write(temp);

    ++boolCount;
}

bool arthlogiCommand(const char* Command[]) {
    if (Command[0][0] == 'n') {
        write("@SP");
        write("A=M-1");

        if (strcmp(Command[0], "not") == 0) {
            write("M=!M");
        } else {
            write("M=-M");
        }
    } else {
        write("@SP");
        write("AM=M-1");
        write("D=M");
        write("A=A-1");

        if (strcmp(Command[0], "add") == 0)
            write("M=D+M");
        else if (strcmp(Command[0], "sub") == 0)
            write("M=M-D");
        else if (strcmp(Command[0], "and") == 0)
            write("M=D&M");
        else if (strcmp(Command[0], "or") == 0)
            write("M=D|M");
        else if (strcmp(Command[0], "eq") == 0)
            booleanPush("JEQ");
        else if (strcmp(Command[0], ) == 0)
            booleanPush("JGT");
        else if (strcmp(Command[0], ) == 0)
            booleanPush("JLT");
        else
            return false;
    }

    return true;
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
    if (Command[0] == NULL)
        return;

    fprintf(writeFile, "// ");
    for (int i = 0; Command[i] != NULL; ++i) {
        fprintf(writeFile, Command[i]);
    }
    fprintf(writeFile, "\n");
}


void VMCodeTranslator(char* filePath) {
    const int separatorIndex = strrchr(filePath, kPathSeparator) - filePath;
    const int dotIndex = strrchr(filePath, '.') - filePath;
    fileName = substring(separatorIndex, dotIndex, filePath);
    fileNameLength = dotIndex - separatorIndex;

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