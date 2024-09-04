//
// Created by cu001 on 4/9/24.
//

#include "AssemblerSecondPass.h"

#include <assert.h>
#include <ctype.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../../helper/hashmap.h"
#include "../../helper/myhashmap.h"
#include "AsssemblerFirstPass.h"

int freeMemory = 16;
struct hashmap *jumpTable;
struct hashmap *compTable;
struct hashmap *symbolTable;

void createJumpTable();
void createCompTable();

char *strip(char *str)
{
    // Trim leading space
    while(isspace((unsigned char)*str)) str++;

    if(*str == 0)
        return str;

    // Trim trailing space
    char *end = str + strlen(str) - 1;
    while(end > str && isspace((unsigned char)*end)) end--;

    end[1] = '\0';

    return str;
}

bool myisNumber(const char *str) {
    while (isdigit(*str)) str++;

    if (*str == 0 || isspace((unsigned char)*str))
        return true;

    return false;
}

char* handleAInstruction(char* instruction) {
    char* usefulInstruction = instruction + 1;

    if (myisNumber(usefulInstruction)) {
        return intToBinary(atoi(usefulInstruction), instruction);
    }

    char* temp = myhashmap_get(symbolTable, usefulInstruction);
    if (temp != NULL)
        return temp;

    char buffer[20];
    myhashmap_set(symbolTable, usefulInstruction, intToBinary(freeMemory++, buffer));
    return myhashmap_get(symbolTable, usefulInstruction);
}

char* handleCInstruction(char* instruction) {
    return "";
}

char* handleInstruction(char *instruction) {
    if (isBlank(instruction) || instruction[0] == '(')
        return NULL;

    if (instruction[0] == '@')
        return handleAInstruction(instruction);

    return handleCInstruction(instruction);
}

void assembleSecondPass(char* fileName, struct hashmap* st) {
    symbolTable = st;

    createCompTable();
    createJumpTable();

    int p = strchr(fileName, '.') - fileName;
    char outputName[p + 5];
    strncpy(outputName, fileName, p);
    outputName[p] = '\0';
    strcat(outputName, ".hack");

    char inst[100];
    FILE* file = fopen(fileName, "r");
    FILE* output = fopen(outputName, "w+");

    if (file == NULL) {
        printf("Error opening file %s\n", fileName);
        exit(1);
    }

    while (fgets(inst, sizeof(inst), file)) {
        const char* temp = strstr(inst, "//");
        char* assembledInst;

        if (temp == NULL) {
            assembledInst = handleInstruction(strip(inst));
        } else {
            const int pos = temp - inst;
            assembledInst = handleInstruction(strip(substring(0, pos, inst)));
        }

        if (assembledInst != NULL) {
            fprintf(output, "%s\n", assembledInst);
        }
    }

    fclose(file);
    fclose(output);

    hashmap_free(jumpTable);
    hashmap_free(compTable);
}

void createCompTable() {
    compTable = myhashmap_new();

    myhashmap_set(compTable, "0", "0101010");
    myhashmap_set(compTable, "1", "0111111");
    myhashmap_set(compTable, "-1", "0111010");
    myhashmap_set(compTable, "D", "0001100");
    myhashmap_set(compTable, "A", "0110000");
    myhashmap_set(compTable, "M", "1110000");
    myhashmap_set(compTable, "!D", "0001101");
    myhashmap_set(compTable, "!A", "0110001");
    myhashmap_set(compTable, "!M", "1110001");
    myhashmap_set(compTable, "-D", "0001111");
    myhashmap_set(compTable, "-A", "0110011");
    myhashmap_set(compTable, "-M", "1110011");
    myhashmap_set(compTable, "D+1", "0011111");
    myhashmap_set(compTable, "A+1", "0110111");
    myhashmap_set(compTable, "M+1", "1110111");
    myhashmap_set(compTable, "D-1", "0001110");
    myhashmap_set(compTable, "A-1", "0110010");
    myhashmap_set(compTable, "M-1", "1110010");
    myhashmap_set(compTable, "D+A", "0000010");
    myhashmap_set(compTable, "D+M", "1000010");
    myhashmap_set(compTable, "D-A", "0010011");
    myhashmap_set(compTable, "D-M", "1010011");
    myhashmap_set(compTable, "A-D", "0000111");
    myhashmap_set(compTable, "M-D", "1000111");
    myhashmap_set(compTable, "D&A", "0000000");
    myhashmap_set(compTable, "D&M", "1000000");
    myhashmap_set(compTable, "D|A", "0010101");
    myhashmap_set(compTable, "D|M", "1010101");
}

void createJumpTable() {
    jumpTable = myhashmap_new();

    myhashmap_set(jumpTable, "JGT", "001");
    myhashmap_set(jumpTable, "JEQ", "010");
    myhashmap_set(jumpTable, "JGE", "011");
    myhashmap_set(jumpTable, "JLT", "100");
    myhashmap_set(jumpTable, "JNE", "101");
    myhashmap_set(jumpTable, "JLE", "110");
    myhashmap_set(jumpTable, "JMP", "111");
}