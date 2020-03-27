#include <stdio.h>
#include <stdlib.h>

#include "glib.h"

int main(int argc, char** argv){

    if(argc < 4){
        printf("faiil: cmd <n_of_node> <n_of_group> <p> <q>");
        exit(EXIT_FAILURE);
    }

    unsigned long   n = atol(argv[1]);
    int g = atoi(argv[2]);

    float p = atof(argv[2]);
    float q = atof(argv[4]);
    generate_clusters(n,g,p,q);
}

