// Online C compiler to run C program online
#include <stdio.h>
#include <string.h>

#define DIRSIZ 14
#define NBUF 16

typedef unsigned int uint;

struct node {
    char name[DIRSIZ];    
};

struct htable {
    uint capacity;
    uint nkeys;
    struct node nodes[NBUF];
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


void displaytable(struct htable *t) {
    int i;
    
    struct node *n;
   
    for(i = 0; i < t->capacity; i++) {
        
        n = &t->nodes[i];
        
        if(strlen(n->name) == 0)
            continue;
        printf("%d | %s\n", i, n->name);
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
    
    while(strncmp(n->name, key, DIRSIZ) != 0) {
       
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
    
    
    while(strlen(n->name) != 0) {
        
        if(strncmp(n->name, key, DIRSIZ) == 0)
            return 1;
        
        index = (++index % t->capacity);
        n = &t->nodes[index];
        collisions++;
        if(collisions == t->capacity) break;
    }
    
    
    if(collisions == t->capacity) {
        return 0;
    }
    
   
    strncpy(n->name, key, DIRSIZ);
    t->nkeys++;
    return 1;
    
}


uint htableremove(struct htable *t, const char *key) {
    struct node *n;
    
    n = htablesearch(t, key);
    
    if(!n) return 0;
    
    strncpy(n->name, "", DIRSIZ);
    
    return 1;
}


void initbcache() {
    memset(&bcachetable, 0, sizeof(struct htable));
    bcachetable.capacity = NBUF;
    
}

int main() {
    
    
    int i;
    char s[DIRSIZ];
    
    // Write C code here
    initbcache();
    
    
    displaytable(&bcachetable);
    
    
   for(i =0; i < bcachetable.capacity; i++) {
       memset(&s, 0, DIRSIZ);
       
       snprintf(s, DIRSIZ, "%d", i);
       htableinsert(&bcachetable, s);
   }
   
    
    
  
    displaytable(&bcachetable);
    
    return 0;
}
