cmake_minimum_required(VERSION 3.29)
project(CProject C)

set(CMAKE_C_STANDARD 17)

add_executable(CProject main.c
        main.c
        helper/hashmap.c
        helper/hashmap.h
        src/HackAssembler/HackAssembler.c
        src/HackAssembler/HackAssembler.h
        src/HackAssembler/AsssemblerFirstPass.c
        src/HackAssembler/AsssemblerFirstPass.h
        helper/myhashmap.c
        helper/myhashmap.h
        tests/MyHashmapTest.c
        tests/Test.h)
