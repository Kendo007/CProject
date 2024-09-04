//
// Created by cu001 on 1/9/24.
//

#include "HackAssembler.h"
#include "AsssemblerFirstPass.h"
#include "../../helper/hashmap.h"

void HackAssembler(const char* fileName) {
    struct hashmap* symbolTable = assembleFirstPass(fileName);

    hashmap_free(symbolTable);
}
