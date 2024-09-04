//
// Created by cu001 on 4/9/24.
//

#include <string.h>
#include "hashmap.h"
#include "myhashmap.h"

#include <stdlib.h>

int user_compare(const void *a, const void *b, void *udata) {
    const blob *ba = a;
    const blob *bb = b;
    return strcmp(ba->key, ba->key);
}

uint64_t user_hash(const void *item, uint64_t seed0, uint64_t seed1) {
    const blob *entry = item;
    return hashmap_sip(entry->key, strlen(entry->key), seed0, seed1);
}

// Freeing all the memory in a blob
void free_blob(const blob* entry) {
    free(entry->key);
    free(entry->value);
}

// Returns a normal hashmap but with functions added and everything
// You can pass cap, seed0, seed1 if not everything defaults too 0
struct hashmap *myhashmap_new() {
    return hashmap_new(sizeof(blob), 0, 0, 0, user_hash, user_compare, free_blob, NULL);
}

// Allocating memory inside the class so as to make easier compatibility
const void* myhashmap_set(struct hashmap *map, const char* key, const char* value) {
    const int key_size = strlen(key);
    char* key_copy = malloc(key_size + 1);
    strncpy(key_copy, key, key_size);

    const int value_size = strlen(value);
    char* value_copy = malloc(value_size + 1);
    strncpy(value_copy, value, value_size);

    const blob temp = {.key = key_copy, .value = value_copy};

    return hashmap_set(map, &temp);
}

char* myhashmap_get(struct hashmap *map, char* key) {
    const blob* temp = (blob*) hashmap_get(map, &(blob) { .key = key });

    if (temp == NULL) {
        return NULL;
    }

    return temp->value;
}
