//
// Created by MARECHAL Anthony & MOZDZIERZ Ombeline on 16/10/2018.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define _CONST1 32

long bs = 0, cs = 0, assoc = 0,
    blockOffsetBits = 0, set = 0, indexBits = 0, tagBits = 0;
char *trace;

typedef struct Cache {
    int valid;
    double tag[32];
} Cache;

// Cache initializer -> cache = null
void initialize(long nbe, long assoc, Cache cache[]){
    int i, j;
    for (i = 0; i < nbe; i++){
        for (j = 0; j < assoc; j++)
            cache[i].tag[j] = -1;
        cache[i].valid = 0;
    }
}

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
            trace = argvs[i];
            i++;
        } else {
            help();
        }
    }
}

// Print out cache configuration
void cacheConfig(){
    puts("Cache configuration :");
    puts(" _______________________________________ ");
    puts("|\tVariable\t\t\t|\tValue\t\t|");
    puts("|-----------------------|---------------|");
    printf("|\tCache size\t\t\t|\t%li\t\t\t|\n", cs);
    printf("|\tCache bloc size\t\t|\t%li\t\t|\n", bs);
    printf("|\tCache associativity\t|\t%li\t\t\t|\n", assoc);
    printf("|\tTrace\t\t\t\t|\t%s\t|\n", trace);
    puts("|_______________________|_______________|");
}

// Convert into bits the tag, index, blockoffset
void bitConverter(){
    blockOffsetBits = (long)(log(bs)/log(2));
    set = (cs*1024)/(bs*assoc);
    indexBits = (long)(log(set)/log(2));
    tagBits = 32 - indexBits - blockOffsetBits;
}

int main(int argc, char **argv) {

    commandParser(argc, argv);
    cacheConfig();
    bitConverter();

    char in[_CONST1];
    char out[_CONST1];
    char tagBin[_CONST1];
    char index[_CONST1];
    char blocOffset[_CONST1];

    Cache cache[set];

    initialize(set, assoc, cache);

    
}
