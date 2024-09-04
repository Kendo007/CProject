//
// Created by cu001 on 1/9/24.
//

#include "AsssemblerFirstPass.h"

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <ctype.h>
#include <string.h>

#include "../../helper/hashmap.h"
#include "../../helper/myhashmap.h"

// Converts the given integer into 16-bit binary string
char* intToBinary(unsigned int n, char binary[]) {
    for (int i = 15; i >= 0; i--) {
        binary[15 - i] = (n & (1 << i)) ? '1' : '0';
    }

    binary[16] = '\0';

    return binary;
}

// Creates a symbol table with values
void createSymbolTable(struct hashmap* symbolTable) {
    char buffer[20];

    for (int i = 0; i < 16; ++i) {
        char temp[5];
        snprintf(temp, 5, "R%d", i);

        myhashmap_set(symbolTable, temp, intToBinary(i, buffer));
    }

    myhashmap_set(symbolTable, "SCREEN",intToBinary(16384, buffer));
    myhashmap_set(symbolTable, "KBD", intToBinary(24576, buffer));
    myhashmap_set(symbolTable, "SP", intToBinary(0, buffer));
    myhashmap_set(symbolTable, "LCL", intToBinary(1, buffer));
    myhashmap_set(symbolTable, "ARG", intToBinary(2, buffer));
    myhashmap_set(symbolTable, "THIS", intToBinary(3, buffer));
    myhashmap_set(symbolTable, "THAT", intToBinary(4, buffer));
}

// Strips the leading whitespaces from the string
char* stripLeadingSpaces(char* str) {
    while(isspace((unsigned char) *str))
        str++;

    return str;
}

// Creates a substring given two index
// Modifies the original string
char* substring(const int index1, const int index2, char str[]) {
    char* substring = str + index1;
    str[index2] = '\0';

    return substring;
}

// Return true if the string consists of only whitespaces
bool isBlank(const char* str) {
    while(isspace((unsigned char) *str))
        str++;

    if (*str == '\0')
        return true;

    return false;
}

// Going through the file creating a symbol table of address in Hack assembly
struct hashmap* assembleFirstPass(const char* fileName) {
    int count = 0;
    struct hashmap *symbolTable = myhashmap_new();
    createSymbolTable(symbolTable);

    char buffer[100];
    FILE* file = fopen(fileName, "r");

    if (file == NULL) {
        printf("Error opening file %s\n", fileName);
        exit(1);
    }

    while (fgets(buffer, sizeof(buffer), file)) {
        char* line = stripLeadingSpaces(buffer);

        if (strlen(line) < 2 || isBlank(line) || (line[0] == '/' && line[1] == '/')) {
            continue;
        }

        if (line[0] == '(') {
            char binary[20];
            const long int l = strchr(line, ')') - line;

            myhashmap_set(symbolTable, substring(1, l, line), intToBinary(count--, binary));
        }

        ++count;
    }

    fclose(file);

    return symbolTable;
}
