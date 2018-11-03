//
// Created by MARECHAL Anthony & MOZDZIERZ Ombeline on 16/10/2018.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>


typedef struct Block {
    short nruB;
    long int tag;
    struct Block *next;
} Block;

typedef struct Set {
    int content;
    struct Block *head;
} Set;

int sets = 0, bs = 0, cs = 0, blockSet = 1, assoc = 0;

int nbr_r = 0, nbr_w = 0, hits_r = 0, hits_w = 0, misses_r = 0, misses_w = 0, hits = 0, misses = 0;

char *trace = NULL;

// Print out cache content
void printCache(Set *cache) {
    int i;
    puts("START");
    for (i = 0; i < sets; i++) {
        struct Block *tmp = cache[i].head;
        while (tmp != NULL) {
            printf("%lu -> ", tmp->tag);
            tmp = tmp->next;
        }
        puts("\nEND");
    }
}

void addToEnd(Set *cache, int setIndex, long int tag) {

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

void newNRU(Set *cache, long int tagBVal, int setIndex) {

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

void nru(Set *cache, long int tagBVal, int setIndex, int wr) {

    struct Block *tmp = cache[setIndex].head;

    int found = 0;

    while (tmp != NULL) {
        if (tmp->tag == tagBVal) {
            tmp->nruB = 0;
            hits++;
            if(wr == 0)
                hits_r++;
            else if(wr == 1)
                hits_w++;
            // puts("Hit");
            found = 1;
            break;
        } else {
            tmp = tmp->next;
        }
    }

    if (found == 0) {
        misses++;
        if(wr == 0)
            misses_r++;
        else if(wr == 1)
            misses_w++;
        // puts("Miss");
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

    blockSet = assoc;

    Set cache[sets];

    // printf("Cache : %d | Block : %d | Set : %d.\n", cs, bs, sets);

    char car, adr[10];

    for (i = 0; i < sets; i++) {
        cache[i].head = NULL;
        cache[i].content = 0;
    }

    long int val;


    while (!feof(tr)) {

        fscanf(tr, "%c%s\n", &car, adr);

        val = strtol(adr, NULL, 16);

        long int numBloc = val / bs;

        int nbe = cs/(bs*assoc);

        long int index = numBloc%nbe;

        long int tag = numBloc/nbe;

        //printf("%c est caractère, %s est adresse\n", car, adr);


        if (car == 'R') {

            nbr_r++;
            nru(cache, tag, index, 0);

        } else if (car == 'W') {

            nbr_w++;
            nru(cache, tag, index, 1);

        }
    }

    // printCache(cache);

    printf("Nombre de lectures : %d.\n"
           "Nombre d'écritures : %d.\n\n"
           "Cohérences lues : %d.\n"
           "Cohérences écrites : %d.\n\n"
           "Défauts lus : %d.\n"
           "Défauts écrits : %d.\n\n"
           "Total de cohérences : %d.\n"
           "Total de défauts : %d.\n",
           nbr_r, nbr_w, hits_r, hits_w, misses_r, misses_w, hits, misses);

    return 0;
}