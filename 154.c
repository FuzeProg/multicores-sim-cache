//
// Created by MARECHAL Anthony & MOZDZIERZ Ombeline on 16/10/2018.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>


typedef struct Block {
    short nruB;
    unsigned long long int tag;
    struct Block *next;
} Block;

typedef struct Set {
    int content;
    struct Block *head;
} Set;

int sets = 0, bs = 0, cs = 0, blockSet = 1, assoc = 0;

int nbr_r = 0, nbr_w = 0, hits = 0, misses = 0;

char *trace = NULL;

// Print out cache content
void printCache(Set *cache) {
    int i;
    for (i = 0; i < sets; i++) {
        struct Block *tmp = cache[i].head;
        while (tmp != NULL) {
            printf("%llu : ", tmp->tag);
            tmp = tmp->next;
        }
        puts("");
    }
    printf("\t\t| END\n");
}

void addToEnd(Set *cache, int setIndex, unsigned long long int tag) {

    struct Block *node = (struct Block *) (malloc(sizeof(struct Block)));

    node->tag = tag;
    node->next = NULL;
    node->nruB = 0;

    if (cache[setIndex].head == NULL) {

        cache[setIndex].head = node;

    } else {

        struct Block *tmp = cache[setIndex].head;

        while (tmp != NULL) {
            if (tmp->next == NULL) {

                tmp->next = node;
                break;

            } else {

                tmp = tmp->next;

            }
        }
    }

    cache[setIndex].content = cache[setIndex].content + 1;
}

void newNRU(Set *cache, unsigned long long int tagBVal, int setIndex) {

    struct Block *tmp = cache[setIndex].head;

    int found = 0;

    while (tmp != NULL) {
        if (tmp->nruB == 1) {

            tmp->nruB = 0;
            tmp->tag = tagBVal;
            found = 1;
            break;

        } else {

            tmp = tmp->next;

        }
    }

    struct Block *fill = cache[setIndex].head;

    if (found == 0) {
        while ((fill != NULL) && (fill->nruB == 0)) {

            fill->nruB = 1;
            fill = fill->next;

        }

        newNRU(cache, tagBVal, setIndex);

    }
}

void nru(Set *cache, unsigned long long int tagBVal, int setIndex, int rewrite) {

    struct Block *tmp = cache[setIndex].head;

    int found = 0;

    while (tmp != NULL) {
        if (tmp->tag == tagBVal) {

            tmp->nruB = 0;

            hits++;


            found = 1;
            break;

        } else {

            tmp = tmp->next;

        }
    }

    if (found == 0) {


        misses++;
        if (cache[setIndex].content < blockSet) {

            addToEnd(cache, setIndex, tagBVal);

        } else {

            newNRU(cache, tagBVal, setIndex);

        }
    }
}

int main(int argc, char **argv) {

    char *tmp;

    cs = (int) strtol(argv[1], &tmp, 10);
    bs = (int) strtol(argv[2], &tmp, 10);
    assoc = (int) strtol(argv[2], &tmp, 10);
    trace = argv[4];

    FILE *tr = fopen(trace, "r");

    if ((!tr) || (argc != 5)) {
        perror("Erreur\n");
        exit(0);
    }

    double csCheck = log((double) cs) / log(2);
    double bsCheck = log((double) bs) / log(2);

    if ((csCheck != (int) csCheck) || (bsCheck != (int) bsCheck)) {
        perror("Erreur\n");
        exit(0);
    } else {
        cs = (int) csCheck;
        bs = (int) bsCheck;
    }

    int i;

    sets = (int) (pow(2, cs) / ((pow(2, bs)) * assoc));

    blockSet = assoc;

    Set cache[sets];

    printf("Cache : %d, | Block : %d | Set : %d.\n", cs, bs, sets);

    char car, adr[10];

    for (i = 0; i < sets; i++) {
        cache[i].head = NULL;
        cache[i].content = 0;
    }

    unsigned long long int val;
    int bitNum = (int) (log(sets) / log(2));

    while (!feof(tr)) {

        fscanf(tr, "%c%s\n", &car, adr);

        val = strtoull(adr, NULL, 16);

        printf("%c est caractere, %s est adresse\n", car, adr);

        unsigned long long int tagBitsValue = (val >> (bs + bitNum));

        int indexBinNum = (int) ((val >> bs) & ((int) (pow(2, bitNum) - 1)));

        if (car == 'R') {

            nbr_r++;
            nru(cache, tagBitsValue, indexBinNum, 0);

        } else if (car == 'W') {

            nbr_w++;
            nru(cache, tagBitsValue, indexBinNum, 1);

        }
    }


    printf("Memoire lues : %d.\n"
           "Memoire ecrites : %d.\n"
           "Hits : %d.\n"
           "Misses : %d.\n",
           nbr_r, nbr_w, hits, misses);

    return 0;
}