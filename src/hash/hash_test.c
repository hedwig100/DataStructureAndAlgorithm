#include <stdio.h>
#include <assert.h>
#include "hash.h"

void test1() {
    Hash* h = make_hash(HASH_SIZE,0,0);
    int a[12] = {0,1,2,3,4,5,1,4,3,2,5,0}; 
    for (int i = 0;i < 12;++i) {
        HashData* hd = make_hash_data(a[i]);
        if (i < 6) {
            assert(!hash_search(h,hd)); 
            hash_insert(h,hd); 
            assert(hash_count_data(h) == i+1); 
        } else {
            assert(hash_search(h,hd));
            hash_delete(h,hd); 
            assert(hash_count_data(h) == 11-i); 
        }
    }
    printf("PASSED OK!\n");
}

void test2() {
    Hash* h = make_hash(HASH_SIZE,0,0);
    assert(hash_count_data(h) == 0);

    HashData* hd = make_hash_data(10); 
    hash_insert(h,hd); 
    assert(hash_count_data(h) == 1); 

    hd = make_hash_data(6); 
    hash_insert(h,hd); 
    assert(hash_count_data(h) == 2); 

    hd = make_hash_data(1094); 
    hash_insert(h,hd); 
    assert(hash_count_data(h) == 3); 
    assert(hash_search(h,hd)); 
    hash_delete(h,hd); 
    assert(!hash_search(h,hd)); 
    assert(hash_count_data(h) == 2);

    hd = make_hash_data(19881); 
    hash_insert(h,hd); 
    assert(hash_count_data(h) == 3); 
    assert(hash_search(h,hd)); 
    hash_delete(h,hd); 
    assert(!hash_search(h,hd)); 
    assert(hash_count_data(h) == 2);

    hd = make_hash_data(10903); 
    hash_insert(h,hd); 
    assert(hash_count_data(h) == 3); 

    hd = make_hash_data(198931); 
    hash_insert(h,hd); 
    assert(hash_count_data(h) == 4); 

    hd = make_hash_data(10903); 
    assert(hash_search(h,hd)); 
    hash_delete(h,hd); 
    assert(!hash_search(h,hd)); 
    assert(hash_count_data(h) == 3);

    printf("PASSED OK!\n");
}

int main() {
    test1();
    test2();
    return 0;
}