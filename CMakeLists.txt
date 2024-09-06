cmake_minimum_required(VERSION 3.29)
project(CProject C)

set(CMAKE_C_STANDARD 17)

add_executable(CProject main.c
        main.c
        helper/hashmap.c
        helper/hashmap.h
        helper/myhashmap.c
        helper/myhashmap.h
        src/HackAssembler/HackAssembler.c
        src/HackAssembler/HackAssembler.h
        src/HackAssembler/AsssemblerFirstPass.c
        src/HackAssembler/AsssemblerFirstPass.h
        src/HackAssembler/AssemblerSecondPass.c
        src/HackAssembler/AssemblerSecondPass.h
        tests/MyHashmapTest.c
        tests/Test.h
        src/VMEmulator/VMEmulator.c
        src/VMEmulator/VMEmulator.h
        src/VMEmulator/VMParser.c
        src/VMEmulator/VMParser.h
        src/VMEmulator/VMCodeTranslator.c
        src/VMEmulator/VMCodeTranslator.h)
