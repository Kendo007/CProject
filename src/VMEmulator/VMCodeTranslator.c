//
// Created by cu001 on 5/9/24.
//

#include "VMCodeTranslator.h"

#include <stdbool.h>
#include <stdlib.h>
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

    char temp[11];
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
        else if (strcmp(Command[0], "gt") == 0)
            booleanPush("JGT");
        else if (strcmp(Command[0], "lt") == 0)
            booleanPush("JLT");
        else
            return false;
    }

    return true;
}

bool branchingCommand(const char* Command[]) {
    int c1 = strlen(Command[1]);

    if (strcmp(Command[0], "label") == 0) {
        char temp[4 + currFunctionLength + c1];
        snprintf(temp, 4 + currFunctionLength + c1, "(%s$%s)", currFunction, Command[1]);

        write(temp);
    } else if (strcmp(Command[0], "goto") == 0) {
        char temp[3 + currFunctionLength + c1];
        snprintf(temp, 3 + currFunctionLength + c1, "@%s$%s", currFunction, Command[2]);

        write(temp);
    } else if (strcmp(Command[0], "if-goto") == 0) {
        write("@SP");
        write("M=M-1");
        write("A=M");
        write("D=M");

        char temp[3 + currFunctionLength + c1];
        snprintf(temp, 3 + currFunctionLength + c1, "@%s$%s", currFunction, Command[2]);

        write(temp);
        write("D;JNE");
    } else {
        return false;
    }

    return true;
}

void helperCall(const char* addr) {
    write(addr);
    if (strchr(addr, '.') != NULL) {
        write("D=A");
    } else {
        write("D=M");
    }
    write("@SP");
    write("M=M+1");
    write("A=M-1");
    write("M=D");
}

void commonCall() {
    write("(FUNCTION)");
    helperCall("@LCL");
    helperCall("@ARG");
    helperCall("@THIS");
    helperCall("@THAT");

    // Setting Up New ARG
    write("@R13");
    write("D=M");
    write("@ARG");
    write("M=D");

    // Setting Up new LCL
    write("@SP");
    write("D=M");
    write("@LCL");
    write("M=D");

    write("@R14");
    write("A=M");
    write("0;JMP");

    wroteCall = true;
}

void writeCall(const char* Command[]) {
    // Storing value of new ARG in temp variable R13
    write("@" + atoi(Command[2]));
    write("D=A");
    write("@SP");
    write("D=M-D");
    write("@R13");
    write("M=D");

    // Pushing returnAddress on stack
    char temp[13 + currFunctionLength];
    snprintf(temp, 13 + currFunctionLength, "@%s$ret.%d", currFunction, callCount);
    helperCall(temp);

    // Storing the function address in temp variable R14
    int c1 = strlen(Command[1]);
    char temp2[c1 + 2];
    snprintf(temp2, c1 + 2, "@%s", Command[1]);

    write(temp2);
    write("D=A");
    write("@R14");
    write("M=D");
    write("@FUNCTION");
    write("0;JMP");

    if (!wroteCall)
        commonCall();

    snprintf(temp, 13 + currFunctionLength, "(%s$ret.%d)", currFunction, callCount);
    write(temp);

    ++callCount;
}

void writeFunction(const char* Command[]) {
    currFunction = (char*) Command[1];
    currFunctionLength = strlen(currFunction);

    char temp[3 + currFunctionLength];
    snprintf(temp, 3 + currFunctionLength, "(%s)", currFunction);
    write(temp);

    if (strcmp(Command[2], "0") != 0) {
        const int c2 = strlen(Command[2]);
        char temp2[c2 + 2];
        snprintf(temp2, c2 + 2, "@%s", Command[2]);

        write(temp2);                    // pushing 0 nVar times
        write("D=A");

        char temp3[15];
        snprintf(temp3, 15, "(PushZero%d)", boolCount);
        write(temp3);
        write("@SP");
        write("M=M+1");
        write("A=M-1");
        write("M=0");
        write("D=D-1");

        snprintf(temp3, 15, "@PushZero%d", boolCount);
        write(temp3);
        write("D;JGT");

        ++boolCount;
    }
}

void helperReturn(const char* addr) {
    write("@endframe");
    write("AM=M-1");
    write("D=M");
    write(addr);
    write("M=D");
}

void commonReturn() {
    write("(RETURN)");
    write("@LCL");           // endframe = LCL
    write("D=M");
    write("@endframe");
    write("M=D");
    write("@5");            // returnArr = *(endframe - 5)
    write("D=A");
    write("@endframe");
    write("A=M-D");
    write("D=M");
    write("@retAddr");
    write("M=D");
    write("@SP");            // *ARG = pop()
    write("A=M-1");
    write("D=M");
    write("@ARG");
    write("A=M");
    write("M=D");
    write("@ARG");
    write("D=M");
    write("@SP");
    write("M=D+1");

    helperReturn("@THAT");
    helperReturn("@THIS");
    helperReturn("@ARG");
    helperReturn("@LCL");

    write("@retAddr");      // goto retAddr
    write("A=M");
    write("0;JMP");

    wroteReturn = true;
}

bool functionCommand(const char* Command[]) {
    if (strcmp(Command[0], "call") == 0) {
        writeCall(Command);
    } else if (strcmp(Command[0], "function") == 0) {
        writeFunction(Command);
    } else if (strcmp(Command[0], "return") == 0) {
        write("@RETURN");
        write("0;JMP");

        if (!wroteReturn)
            commonReturn();
    } else {
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

    if (memoryCommand(Command) || branchingCommand(Command) || functionCommand(Command) || arthlogiCommand(Command)) {
    } else {
        printf("Something is not right!!\n");
    }
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