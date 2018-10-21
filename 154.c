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

// Hexadecimal converter to binary
void hexaConverter(char in[], char out[]) {
    int i, j;
    size_t size = strlen(in);

    for (i = 0; i < size; i++) {
        if (in[i] == 0) {
            out[i*4] = '0';
            out[i*4+1] = '0';
            out[i*4+2] = '0';
            out[i*4+3] = '0';
        } else if (in[i] == '1') {
            out[i*4] = '0';
            out[i*4+1] = '0';
            out[i*4+2] = '0';
            out[i*4+3] = '1';
        } else if (in[i] == '2') {
            out[i*4] = '0';
            out[i*4+1] = '0';
            out[i*4+2] = '1';
            out[i*4+3] = '0';
        } else if (in[i] == '3') {
            out[i*4] = '0';
            out[i*4+1] = '0';
            out[i*4+2] = '1';
            out[i*4+3] = '1';
        } else if (in[i] == '4') {
            out[i*4] = '0';
            out[i*4+1] = '1';
            out[i*4+2] = '0';
            out[i*4+3] = '0';
        } else if (in[i] == '5') {
            out[i*4] = '0';
            out[i*4+1] = '1';
            out[i*4+2] = '0';
            out[i*4+3] = '1';
        } else if (in[i] == '6') {
            out[i*4] = '0';
            out[i*4+1] = '1';
            out[i*4+2] = '1';
            out[i*4+3] = '0';
        } else if (in[i] == '7') {
            out[i*4] = '0';
            out[i*4+1] = '1';
            out[i*4+2] = '1';
            out[i*4+3] = '1';
        } else if (in[i] == '8') {
            out[i*4] = '1';
            out[i*4+1] = '0';
            out[i*4+2] = '0';
            out[i*4+3] = '0';
        } else if (in[i] == '9') {
            out[i*4] = '1';
            out[i*4+1] = '0';
            out[i*4+2] = '0';
            out[i*4+3] = '1';
        } else if (in[i] == 'a') {
            out[i*4] = '1';
            out[i*4+1] = '0';
            out[i*4+2] = '1';
            out[i*4+3] = '0';
        } else if (in[i] == 'b') {
            out[i*4] = '1';
            out[i*4+1] = '0';
            out[i*4+2] = '1';
            out[i*4+3] = '1';
        } else if (in[i] == 'c') {
            out[i*4] = '1';
            out[i*4+1] = '1';
            out[i*4+2] = '0';
            out[i*4+3] = '0';
        } else if (in[i] == 'd') {
            out[i*4] = '1';
            out[i*4+1] = '1';
            out[i*4+2] = '0';
            out[i*4+3] = '1';
        } else if (in[i] == 'e') {
            out[i*4] = '1';
            out[i*4+1] = '1';
            out[i*4+2] = '1';
            out[i*4+3] = '0';
        } else if (in[i] == 'f') {
            out[i*4] = '1';
            out[i*4+1] = '1';
            out[i*4+2] = '1';
            out[i*4+3] = '1';
        }
    }
    out[size*4] = '\0';
}


int main(int argc, char *argv[]) {
    long i = 1, cs, bs, assoc;
    char *tmp;

    // Command line arguments parser, assign the values
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
        } else if (strcmp("-a", argv[i]) == 0) {
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

    // Cache configuration
    puts("Cache configuration :");
    printf("Cache size\t\t\t\t%li.\n", cs);
    printf("Cache bloc size\t\t\t%li.\n", bs);
    printf("Cache associativity\t\t%li.\n", assoc);
    puts("");
}
