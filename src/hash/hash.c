#include "hash.h"

static const long long P = 4053946;
static const int MASK = HASH_SIZE-1; 
static const int B = 1093; // random 

// if hash_size == HASH_SIZE: a,b are ignored 
// else: all params are used
int calc_hash(int value,int hash_size,int a,int b) {
    if (hash_size == HASH_SIZE) return (int)(((value << 5) + B)%P)&MASK; // A = 1<<5,key = (A*value + B)
    else return (a*value + b)%P%hash_size; 
}

HashData* make_hash_data(int value) {
    HashData* hd = malloc(sizeof(HashData));
    if (hd == NULL) exit(1);
    hd->value = value; 
    hd->next = NULL; 
    hd->prev = NULL;
    return hd; 
}

Hash* make_hash(int n,int a,int b) {
    Hash* h = malloc(sizeof(Hash)); 
    if (h == NULL) exit(1);
    h->size = n;
    h->a = a; 
    h->b = b;

    HashData** table = malloc(n*sizeof(HashData*)); 
    if (table == NULL) exit(1);
    for (int i = 0;i < n;i++) {
        table[i] = NULL; 
    }
    h->table = table;
    return h;
}

void hash_insert(Hash* h,HashData* hd) {
    int key = calc_hash(hd->value,h->size,h->a,h->b);
    if (h->table[key]) {
        hd->next = h->table[key]; 
        h->table[key]->prev = hd; 
        h->table[key] = hd;
    } else {
        h->table[key] = hd; 
    }
}

bool hash_search(Hash* h,HashData* hd) {
    int key = calc_hash(hd->value,h->size,h->a,h->b);  
    if (h->table[key]) {
        for (HashData* p = h->table[key];p != NULL;p = p->next) {
            if (p->value == hd->value) {
                return true;
            }
        }
    } else {
        return false; 
    }
    return false;
}

// hdがhに入っていることはsearchなどで確認してからdeleteする
void hash_delete(Hash* h,HashData* hd) {
    int key = calc_hash(hd->value,h->size,h->a,h->b); 
    for (HashData* p = h->table[key];p != NULL;p = p->next) {
        if (p->value != hd->value) continue; 
        if (p->next == NULL && p->prev == NULL) {
            h->table[key] = NULL; 
            free(p);
            return; 
        } else if (p->next == NULL) {
            (p->prev)->next = NULL; 
            free(p);
            return;
        } else if (p->prev == NULL) {
            h->table[key]->next = p->next; 
            free(p);
            return; 
        } else {
            (p->prev)->next = p->next; 
            (p->next)->prev = p->prev;
            free(p);
            return; 
        }
    }
}

int hash_count_data(Hash* h) {
    int count = 0;
    for (int key = 0;key < h->size;key++) {
        for (HashData* p = h->table[key];p != NULL;p = p->next) {
            ++count;
        }
    }
    return count;
}

