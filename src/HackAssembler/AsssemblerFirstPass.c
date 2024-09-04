//
// Created by cu001 on 1/9/24.
//

#include "AsssemblerFirstPass.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../../helper/hashmap.h"
#include "../../helper/myhashmap.h"

// Reverses a given string and pad it with 0s
char* reverseAndPadString(char str[], int size) {
    for (int i = 0; i < size / 2; i++) {
        const char temp = str[i];
        str[i] = str[size - i - 1];
        str[size - i - 1] = temp;
    }



    return str;
}

char* intToBinary(int n, char binary[]) {
    int i = 0;

    while (n > 0) {
        // storing remainder in binary array
        binary[i] = (n % 2) + 48;
        n = n / 2;
        ++i;
    }

    binary[i] = '\0';
    return reverseString(binary, i);
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