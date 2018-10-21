//
// Created by MARECHAL Anthony & MOZDZIERZ Ombeline on 16/10/2018.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

long bs = 0;
long cs = 0;
long assoc = 0;
char *file;

typedef struct s {
    int valid;
    double tag;
} bloc;

/*typedef bloc Cache [][];

void initialise(int nbe, int assoc, Cache cache) {
    int i, j;
    for (i=0; i<nbe; i++)
        for (j=0; j<assoc; j++)
            cache[i][j].valid=0;
}*/

void help() {
    puts("Usage : ./154.c -b -l -a FILE\n");
    printf("  -b cache size : Size of the cache\n");
    printf("  -l bloc size : Blocsize of the cache\n");
    printf("  -a assoc : Associativity of the cache\n");
    printf("  FILE : File that contains traces\n");
    exit(0);
}

int main(int argc, char *argv[]) {
    long i = 1, cs, bs, assoc;
    char *tmp;
    while (i < argc) {
        if (strcmp("-b", argv[i]) == 0) {
            i++;
            if (i >= argc)
                help();
            cs = strtol(argv[i], &tmp, 10);
            i++;
        } else if (strcmp("-l", argv[i]) == 0) {
            i++;
            if (i >= argc)
                help();
            bs = strtol(argv[i], &tmp, 10);
            i++;
        } else if (strcmp ("-a", argv [i]) == 0) {
            i++;
            if (i >= argc)
                help();
            assoc = strtol(argv[i], &tmp, 10);
            i++;
            file = argv[i];
            i++;
        } else {
            help();
        }
    }
    printf("%li %li %li %s", cs, bs, assoc, file);
}
