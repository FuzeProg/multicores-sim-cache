//
// Created by MARECHAL Anthony & MOZDZIERZ Ombeline on 16/10/2018.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>


typedef struct Block {
    short nruB;
    unsigned long int tag;
    struct Block *next;
} Block;

typedef struct Set {
    int content;
    struct Block *head;
    struct Block *queue;
} Set;

int sets = 0, bs = 0, cs = 0, blockNum = 1;

int nbr_r = 0, nbr_w = 0, hits = 0, misses = 0;

// Print out cache configuration
void cacheConfig(int cs, int bs, int assoc, int nbe, char *trace) {
    puts("Cache configuration :");
    printf("Cache size\t\t\t\t%d\n", cs);
    printf("Cache bloc size\t\t\t%d\n", bs);
    printf("Cache associativity\t\t%d\n", assoc);
    printf("Set number\t\t\t\t%d\n", nbe);
    printf("Trace\t\t\t\t\t%s\n", trace);
    puts("");
    puts("");
}

// Print out cache content
void printCache(Set *cache){
    int i;
    for(i = 0; i < sets; i++){
        struct Block *tmp = cache[i].head;
        while(tmp != NULL){
            printf("%lu : ", tmp->tag);
            tmp = tmp->next;
        }
        puts("");
    }
    printf("\t\t| END");
}

void mapping(Set *cache, unsigned long int tagBVal, int setIndex, int swap){
    if((cache[setIndex].head != NULL) &&
            (cache[setIndex].head->tag == tagBVal)){
        if(swap == 0)
            hits++;
        else{
            hits++;
            nbr_w++;
        }
    } else {
        if(swap == 0) {
            misses++;
            nbr_r++;
        } else {
            misses++;
            nbr_r++;
            nbr_w++;
        }
        cache[setIndex].head = (struct Block *)(malloc(sizeof(struct Block)));
        cache[setIndex].head->tag = tagBVal;
    }
}

void enqueue(Set *cache, int index, unsigned long int tag, int swap){
    struct Block *tmp = cache[index].queue;
    cache[index].queue = (struct Block *)(malloc(sizeof(struct Block)));
    cache[index].queue->tag = tag;
    cache[index].queue->next = NULL;

    if(cache[index].head == NULL){
        cache[index].head = cache[index].queue;
        if(swap == 0){
            misses++;
            nbr_r++;
        } else {
            misses++;
            nbr_r++;
            nbr_w++;
        }
    } else{
        if(swap == 0){
            misses++;
            nbr_r++;
        } else {
            misses++;
            nbr_r++;
            nbr_w++;
        }
        tmp->next = cache[index].queue;
    }

    if (cache[index].content < blockNum){
        cache[index].content = cache[index].content + 1;
    }
}

void dequeue(Set *cache, int index, unsigned long int tag, int swap){
    struct Block *tmp = cache[index].head;

    if(cache[index].head != NULL){
        cache[index].head = cache[index].head->next;
        free(tmp);
    }

    dequeue(cache, index, tag, swap);
}

void addToHead(Set *cache, int setIndex, unsigned long int tag){
    struct Block *node = (struct Block *)(malloc(sizeof(struct Block)));
    node->tag = tag;
    node->next = NULL;

    if(cache[setIndex].head == NULL){
        cache[setIndex].head = node;
    } else {
        struct Block *tmp = cache[setIndex].head;
        cache[setIndex].head = node;
        node->next = tmp;
    }

    cache[setIndex].content = cache[setIndex].content + 1;
}

void addToEnd(Set *cache, int setIndex, unsigned long int tag){
    struct Block *node = (struct Block *)(malloc(sizeof(struct Block)));
    node->tag = tag;
    node->next = NULL;
    node->nruB = 0;

    if(cache[setIndex].head == NULL){
        cache[setIndex].head = node;
    } else {
        struct Block *tmp = cache[setIndex].head;

        while(tmp != NULL){
            if(tmp->next == NULL){
                tmp->next = node;
            } else {
                tmp = tmp -> next;
            }
        }
    }

    cache[setIndex].content = cache[setIndex].content + 1;
}

void newNRU(Set *cache, unsigned long int tagBVal, int setIndex){
    struct Block *tmp = cache[setIndex].head;
    int found = 0;

    while (tmp != NULL){
        if(tmp->nruB == 1){
            tmp->nruB = 0;
            tmp->tag = tagBVal;
            found = 1;
        } else
            tmp = tmp->next;
    }

    struct Block *new = cache[setIndex].head;

    if(found == 0){
        while ((new != NULL) && (new->nruB == 0)){
            new->nruB = 1;
            new = new->next;
        }
        newNRU(cache, tagBVal, setIndex);
    }
}

void nru(Set *cache, unsigned long int tagBVal, int setIndex, int swap) {
    struct Block *tmp = cache[setIndex].head;
    int found = 0;

    while(tmp != NULL){
        if(tmp->tag == tagBVal){
            tmp->nruB = 0;
            if(swap == 0)
                hits++;
            else{
                hits++;
                nbr_w++;
            }
            found = 1;
        } else
            tmp = tmp->next;
    }

    if(found == 0){

        if(swap == 0){
            misses++;
            nbr_r++;
        } else {
            misses++;
            nbr_r++;
            nbr_w++;
        }

        if(cache[setIndex].content < blockNum) {
            addToEnd(cache, setIndex, tagBVal);
        } else {
            newNRU(cache, tagBVal, setIndex);
        }
    }
}

int main(int argc, char *argv[]) {

    char *tmp;

    int cs = (int)strtol(argv[1], &tmp, 10);
    int bs = (int)strtol(argv[2], &tmp, 10);
    int assoc = (int) strtol(argv[3], &tmp, 10);
    int nbe = cs/(bs*assoc);
    char *trace = argv[4];


}