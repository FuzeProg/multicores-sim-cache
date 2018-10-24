//
// Created by MARECHAL Anthony & MOZDZIERZ Ombeline on 16/10/2018.
//

#include <stdio.h>
#include <stdlib.h>

typedef struct bloc{
    int valid;
    double tag;
}bloc;

// Cache initializer
void initCache(long nbe, long assoc, bloc cache[nbe][assoc]){
    int i, j;
    for(i = 0; i < nbe; i++)
        for(j = 0; j < assoc; j++)
            cache[i][j].valid = 0;
}

// Print out cache configuration
void cacheConfig(int cs, int bs, int assoc, int nbe, char *trace){
    puts("Cache configuration :");
    printf("Cache size\t\t\t\t%d\n", cs);
    printf("Cache bloc size\t\t\t%d\n", bs);
    printf("Cache associativity\t\t%d\n", assoc);
    printf("Set number\t\t\t\t%d\n", nbe);
    printf("Trace\t\t\t\t\t%s\n", trace);
    puts("");
    puts("");
}


int main(int argc, char *argv[]) {

    char *tmp;
    int nbr_r = 0, nbr_w = 0;

    int cs = (int)strtol(argv[1], &tmp, 10);
    int bs = (int)strtol(argv[2], &tmp, 10);
    int assoc = (int) strtol(argv[3], &tmp, 10);
    int nbe = cs/(bs*assoc);
    char *trace = argv[4];

    bloc cache[nbe][assoc];

    initCache(nbe, assoc, cache);
    cacheConfig(cs, bs, assoc, nbe, trace);

    char car, *adr, i = 0;

    FILE *f = fopen("test.txt", "r");
    if(f != NULL){
        while(!feof(f)){
            fscanf(f, "%c%s\n", &car, adr);
            printf("Ligne %d : %c est un caractère.\n%s est une adresse.\n\n", i, car, adr);
            i++;
        }
    fclose(f);
    }
}
