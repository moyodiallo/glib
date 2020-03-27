#include <stdio.h>
#include <stdlib.h>

#include "constants.h"


int main(int argc, char** argv){

    if (argc < 2) {
        printf("argument not good :cmd <file>");
        return 1;
    }

    FILE* file = fopen(argv[1], "r");

    if(file == NULL){
        printf("fail opening file");
        return 1;
    }

    unsigned long u,v;

    while (fscanf(file,"%lu %lu", &u, &v) == 2)
    {
        if(u < v){
            printf("%lu %lu\n",u,v);
        }else if( v < u){
            printf("%lu %lu\n",v,u);
        }
    }
}
