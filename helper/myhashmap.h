//
// Created by cu001 on 4/9/24.
//

// Added all the base functions for easier usage in my code

#ifndef MYHASHMAP_H
#define MYHASHMAP_H

#include "hashmap.h"

typedef struct {
    char* key;
    char* value;
} blob;

struct hashmap *myhashmap_new();

const void* myhashmap_set(struct hashmap *map, const char* key, const char* value);

char* myhashmap_get(struct hashmap *map, char* key);

#endif //MYHASHMAP_H
