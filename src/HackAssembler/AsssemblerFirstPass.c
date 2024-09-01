//
// Created by cu001 on 1/9/24.
//

#include "AsssemblerFirstPass.h"

char* reverseString(char str[], int size) {
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

