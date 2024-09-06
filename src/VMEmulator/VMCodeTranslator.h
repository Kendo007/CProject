//
// Created by cu001 on 5/9/24.
//

#ifndef VMCODETRANSLATOR_H
#define VMCODETRANSLATOR_H
#include <stdio.h>

extern FILE* writeFile;
extern char kPathSeparator;
extern char* currFunction;

void VMCodeTranslator();
void write(const char* s);
void parseCommand(char* command[], char* line);
void initialiseBaseAddress();
void writeCall(const char* Command[]);

#endif //VMCODETRANSLATOR_H
