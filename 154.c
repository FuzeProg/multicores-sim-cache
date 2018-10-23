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
void cacheConfig(int cs, int bs, int assoc, char *trace){
    puts("Cache configuration :");
    puts(" _______________________________________ ");
    puts("|\tVariable\t\t\t|\tValue\t\t|");
    puts("|-----------------------|---------------|");
    printf("|\tCache size\t\t\t|\t%d\t\t\t|\n", cs);
    printf("|\tCache bloc size\t\t|\t%d\t\t|\n", bs);
    printf("|\tCache associativity\t|\t%d\t\t\t|\n", assoc);
    printf("|\tTrace\t\t\t\t|\t%s\t|\n", trace);
    puts("|_______________________|_______________|");
}


int main(int argc, char *argv[]) {

    char *tmp;

    int cs = (int)strtol(argv[1], &tmp, 10);
    int bs = (int)strtol(argv[2], &tmp, 10);
    int assoc = (int) strtol(argv[3], &tmp, 10);
    char *trace = argv[4];
    int nbe = cs/(bs*assoc);

    bloc cache[nbe][assoc];

    initCache(nbe, assoc, cache);
    cacheConfig(cs, bs, assoc, trace);


}
