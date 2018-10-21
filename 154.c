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

// Print out help for command
void help() {
    puts("Usage : ./154.c -b -l -a FILE\n");
    printf("  -b cache_size : Size of the cache\n");
    printf("  -l bloc_size : Blocsize of the cache\n");
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

// Command line arguments parser, assign the values
void commandParser(int argcs, char **argvs){
    int i = 1;
    char *tmp;

    while (i < argcs) {
        if (strcmp("-b", argvs[i]) == 0) {
            i++;
            if (i >= argcs)
                help();
            cs = strtol(argvs[i], &tmp, 10);
            i++;
        } else if (strcmp("-l", argvs[i]) == 0) {
            i++;
            if (i >= argcs)
                help();
            bs = strtol(argvs[i], &tmp, 10);
            i++;
        } else if (strcmp("-a", argvs[i]) == 0) {
            i++;
            if (i >= argcs)
                help();
            assoc = strtol(argvs[i], &tmp, 10);
            i++;
            file = argvs[i];
            i++;
        } else {
            help();
        }
    }
}

// Print out cache configuration
void cacheConfig(){
    puts("Cache configuration :");
    printf("Cache size\t\t\t\t%li.\n", cs);
    printf("Cache bloc size\t\t\t%li.\n", bs);
    printf("Cache associativity\t\t%li.\n", assoc);
    puts("");
}

int main(int argc, char **argv) {
    char *tmp;

    commandParser(argc, argv);
    cacheConfig();

}
