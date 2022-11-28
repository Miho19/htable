// Online C compiler to run C program online
#include <stdio.h>
#include <string.h>

#define KEYLENGTH 16
#define HTABLESIZE 16

typedef unsigned int uint;

struct node {
    char key[KEYLENGTH];
    void *ptr;
};

struct htable {
    uint capacity;
    uint nkeys;
    struct node nodes[HTABLESIZE];
};


struct htable bcachetable;


static uint htable_word_to_int(const char *word) {
    uint result;
    
    result = 0;
    
    while(*word != '\0'){
        result = (*word + 31 * result);
        word++;
    }
    return result;
}


void displaytable(struct htable *t, void(*printfunc)(int, void *)) {
    int i;
    
    struct node *n;
   
    for(i = 0; i < t->capacity; i++) {
        
        n = &t->nodes[i];
        
        if(strlen(n->key) == 0)
            continue;
        printfunc(i, n);
    }
}

struct node* htablesearch(struct htable *t, const char *key) {
    uint hash;
    uint index;
    uint collisions;
    
    struct node *n;
    
    hash = htable_word_to_int(key);
    index = (hash % t->capacity);
    
    
    n = &t->nodes[index];
    
    collisions = 0;
    
    while(strncmp(n->key, key, KEYLENGTH) != 0) {
       
        collisions++;
        index = (++index % t->capacity);
        if(collisions == t->capacity) break;
        
        n = &t->nodes[index];
        
    }
   
     
    if(collisions == t->capacity) n = 0;
    
      //printf("index %d/%d collisions: %d n->name %s key %s\n", index, t->capacity, collisions,n->name, key);
      
    return n;
}

uint htableinsert(struct htable *t, const char *key) {
    uint hash;
    uint index;
    
    uint collisions;
    
    
    struct node *n;
    
    hash = htable_word_to_int(key);
    index = (hash % t->capacity);
    
    n = &t->nodes[index];
    collisions = 0;
    
    
    while(strlen(n->key) != 0) {
        
        if(strncmp(n->key, key, KEYLENGTH) == 0)
            return 1;
        
        index = (++index % t->capacity);
        n = &t->nodes[index];
        collisions++;
        if(collisions == t->capacity) break;
    }

    if(collisions == t->capacity) {
        return 0;
    }

    strncpy(n->key, key, KEYLENGTH);
    t->nkeys++;
    return 1;
    
}


uint htableremove(struct htable *t, const char *key) {
    struct node *n;
    n = htablesearch(t, key);
    if(!n) return 0;
    strncpy(n->key, "", KEYLENGTH);
    return 1;
}

int main() {
    
    return 0;
}
