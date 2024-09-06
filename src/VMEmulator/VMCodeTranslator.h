//
// Created by cu001 on 5/9/24.
//

#ifndef VMCODETRANSLATOR_H
#define VMCODETRANSLATOR_H
#include <stdio.h>

extern FILE* writeFile;
extern char kPathSeparator;

void VMCodeTranslator();
void write(const char* s);
void parseCommand(char* command[], char* line);

#endif //VMCODETRANSLATOR_H
