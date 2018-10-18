//
// Created by MARECHAL Anthony & MOZDZIERZ Ombeline on 16/10/2018.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

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

void isCorrect(int argcs, char *argvs[]) {
    if (argcs < 5 || argcs > 5) {

        printf("Arguments manquants : \n"
               "1 : programme 154.c. \n"
               "2 : taille du cache. Vous avez saisi : %s\n"
               "3 : taille du bloc. Vous avez saisi : %s\n"
               "4 : degrés d'associativité. Vous avez saisi : %s\n"
               "5 : fichier à parcourir. Vous avez saisi : %s\n",
               argvs[1], argvs[2], argvs[3], argvs[4]);
        exit(1);
    }
}

void test(char *argvs[], int c){
    if(isnumber((int)strtol(argvs[c], NULL, 10)))
        puts("C'est un chiffre");
    else
        puts("C'est un texte");
}

int main(int argc, char *argv[]) {

    long cs, bs, assoc;
    char *tmp, *trace;

    isCorrect(argc, argv);
    test(argv, 1);
    test(argv, 4);
    printf("%li", strtol(argv[4], &tmp, 10));
    exit(1);

    cs = strtol(argv[1], &tmp, 10);
    bs = strtol(argv[2], &tmp, 10);
    assoc = strtol(argv[3], &tmp, 10);
    trace = argv[4];

    printf("%li, %li, %li, %s", cs, bs, assoc, trace);

}
