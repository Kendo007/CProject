//
// Created by cu001 on 1/9/24.
//

#include "AsssemblerFirstPass.h"

#include <stdio.h>
#include <stdlib.h>
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

void intialiseTable(struct hashmap* symbolTable) {
    char buffer[20];

    for (int i = 0; i < 16; ++i) {
        char temp[5];
        snprintf(temp, 5, "R%d", i);

        myhashmap_set(symbolTable, temp, intToBinary(i, buffer));

        printf("Key: %s Value: %s Org: %s\n", temp, myhashmap_get(symbolTable, temp), buffer);
    }

    myhashmap_set(symbolTable, "SCREEN",intToBinary(16384, buffer));
    myhashmap_set(symbolTable, "KBD", intToBinary(24576, buffer));
    myhashmap_set(symbolTable, "SP", intToBinary(0, buffer));
    myhashmap_set(symbolTable, "LCL", intToBinary(1, buffer));
    myhashmap_set(symbolTable, "ARG", intToBinary(2, buffer));
    myhashmap_set(symbolTable, "THIS", intToBinary(3, buffer));
    myhashmap_set(symbolTable, "THAT", intToBinary(4, buffer));
}

void assembleFirstPass(char* fileName) {
    char* key;
    char* value;

    struct hashmap *symbolTable = myhashmap_new();
    intialiseTable(symbolTable);

    hashmap_free(symbolTable);
}