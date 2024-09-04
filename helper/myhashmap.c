//
// Created by cu001 on 4/9/24.
//

#include <string.h>
#include "myhashmap.h"

int user_compare(const void *a, const void *b, void *udata) {
    const blob *ba = a;
    const blob *bb = b;
    return strcmp(ba->key, ba->key);
}

uint64_t user_hash(const void *item, uint64_t seed0, uint64_t seed1) {
    const blob *entry = item;
    return hashmap_sip(entry->key, strlen(entry->key), seed0, seed1);
}