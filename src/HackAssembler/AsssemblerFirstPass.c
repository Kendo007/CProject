//
// Created by cu001 on 1/9/24.
//

#include "AsssemblerFirstPass.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void reverseString(char str[], int size) {
    for (int i = 0; i < size / 2; i++) {
        const char temp = str[i];
        str[i] = str[size - i - 1];
        str[size - i - 1] = temp;
    }
}

void intToBinary(int n, char binary[]) {
    int i = 0;

    while (n > 0) {
        // storing remainder in binary array
        binary[i] = (n % 2) + 48;
        n = n / 2;
        ++i;
    }

    binary[i] = '\0';
    reverseString(binary, i);
}
/*
void intialiseTable(HASHMAP(char*, char*)* symbolTable) {
    hashmap_init(symbolTable, hashmap_hash_string, strcmp);

    for (int i = 0; i < 30; ++i) {
        char temp[5];
        snprintf(temp, 5, "R%d", i);

        char *buffer = malloc(sizeof(char) * 17);
        hashmap_put(symbolTable, temp, buffer);

        intToBinary(i, buffer);
        printf("%p ", buffer);

        printf("Key: %s Value: %p Org: %p\n", temp, hashmap_get(symbolTable, temp), buffer);
    }

    char *buffer = malloc(sizeof(char) * 25);
    intToBinary(16384, buffer);
    hashmap_put(symbolTable, "SCREEN", buffer);
    // hashmap_put(&symbolTable, "KBD", intToBinary(24576, buffer));
    // hashmap_put(&symbolTable, "SP", intToBinary(0, buffer));
    // hashmap_put(&symbolTable, "LCL", intToBinary(1, buffer));
    // hashmap_put(&symbolTable, "ARG", intToBinary(2, buffer));
    // hashmap_put(&symbolTable, "THIS", intToBinary(3, buffer));
    // hashmap_put(&symbolTable, "THAT", intToBinary(4, buffer));
}*/

void assembleFirstPass(char* fileName) {
    char* key;
    char* value;

}