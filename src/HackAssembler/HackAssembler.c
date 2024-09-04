//
// Created by cu001 on 1/9/24.
//

#include "HackAssembler.h"

#include <stdlib.h>

#include "AsssemblerFirstPass.h"
#include "AssemblerSecondPass.h"
#include "../../helper/hashmap.h"

void HackAssembler(char* fileName) {
    struct hashmap* symbolTable = assembleFirstPass(fileName);

    if (symbolTable == NULL) {
        exit(-1);
    }

    assembleSecondPass(fileName, symbolTable);

    hashmap_free(symbolTable);
}
