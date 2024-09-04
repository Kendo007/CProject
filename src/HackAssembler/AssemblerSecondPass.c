//
// Created by cu001 on 4/9/24.
//

#include "AssemblerSecondPass.h"
#include "../../helper/hashmap.h"
#include "../../helper/myhashmap.h"

int freeMemory = 16;
struct hashmap *jumpTable;
struct hashmap *compTable;

void assemblerSecondPass() {

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