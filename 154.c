//
// Created by MARECHAL Anthony & MOZDZIERZ Ombeline on 16/10/2018.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct s{
    int valid;
    double tag;
}bloc;

/*typedef bloc Cache [][];

void initialise(int nbe, int assoc, Cache cache) {
    int i, j;
    for (i=0; i<nbe; i++)
        for (j=0; j<assoc; j++)
            cache[i][j].valid=0;
}*/

int main(int argc, char* argv[]){
int cs, bs, assoc;
char* tmp, trace;

cs = strtol(argv[1], &tmp, 10);
bs = strtol(argv[2], &tmp, 10);
assoc = strtol(argv[3], &tmp, 10);
strcpy(&trace, argv[4]);

printf("%d, %d, %d, %s", cs, bs, assoc, &trace);
}
