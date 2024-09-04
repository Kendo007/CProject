//
// Created by cu001 on 4/9/24.
//

#include <stdio.h>
#include "Test.h"
#include "../helper/myhashmap.h"

void test() {
    // create a new hash map where each item is a `struct user`. The second
    // argument is the initial capacity. The third and fourth arguments are
    // optional seeds that are passed to the following hash function.
    struct hashmap *map = myhashmap_new();

    // Here we'll load some users into the hash map. Each set operation
    // performs a copy of the data that is pointed to in the second argument.
    myhashmap_set(map, "Kendo", "20");
    myhashmap_set(map, "Rupali", "23");
    myhashmap_set(map, "Ash", "15");

    char *value;

    printf("\n-- get some users --\n");
    value =  myhashmap_get(map, "Kendo");
    printf("Kendo age=%s\n", value);

    value =  myhashmap_get(map, "Rupali");
    printf("Rupali age=%s\n", value);

    value =  myhashmap_get(map, "Tom");
    printf("%s\n", value?"exists":"not exists");

    printf("\n-- iterate over all users (hashmap_iter) --\n");
    size_t iter = 0;
    void *item;
    while (hashmap_iter(map, &iter, &item)) {
        const blob *user = item;
        printf("%s (age=%s)\n", user->key, user->value);
    }

    hashmap_free(map);
}