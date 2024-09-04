//
// Created by cu001 on 1/9/24.
//

#ifndef ASSSEMBLERFIRSTPASS_H
#define ASSSEMBLERFIRSTPASS_H

#include "../../helper/hashmap.h"

char* intToBinary(unsigned int n, char binary[]);

struct hashmap* assembleFirstPass(const char* fileName);

char* substring(int index1, int index2, char str[]);

bool isBlank(const char* str);

#endif //ASSSEMBLERFIRSTPASS_H
