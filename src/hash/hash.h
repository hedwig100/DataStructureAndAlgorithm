#ifndef HASH_H
#define HASH_H

#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h> // for debug

// const 
#define HASH_SIZE (1 << 20) 

// calc hash
int calc_hash(int value,int hash_size,int a,int b); 

// hash data
struct HashData; 

typedef struct HashData {
    int value; 
    struct HashData* next; 
    struct HashData* prev; 
} HashData; 

HashData* make_hash_data(int value); 

// hash
typedef struct Hash {
    int size;
    int a,b;
    HashData** table; 
} Hash;

Hash* make_hash(int n,int a,int b); 
void hash_insert(Hash* h,HashData* hd);
bool hash_search(Hash* h,HashData* hd); 
void hash_delete(Hash* h,HashData* hd); 
int hash_count_data(Hash* h);

#endif