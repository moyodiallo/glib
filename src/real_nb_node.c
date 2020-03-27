#include <stdio.h>
#include <stdlib.h>

int main(int argc, char** argv){
    if(argc != 2){
        printf("fail: cmd <file>");
        exit(EXIT_FAILURE);
    }

    unsigned long u,v,i;
    unsigned long n_of_edges = 0;
    unsigned long n_of_nodes = 0;
    unsigned long* nodes;
    unsigned long total = 0;

    FILE *file  = fopen(argv[1],"r");

     while (fscanf(file,"%lu %lu",&u, &v) == 2){
        n_of_edges++;
        if(u > v && u > n_of_nodes){
            n_of_nodes = u;
        }else if(v > u && v > n_of_nodes){
            n_of_nodes = v;
        }
    }

    nodes = calloc(n_of_nodes+1,sizeof(unsigned long));

    fseek(file,0L,SEEK_SET);

    while (fscanf(file,"%lu %lu",&u, &v) == 2){
        nodes[u] = 1;
        nodes[v] = 1;
    }

    for (i = 1; i < n_of_nodes+1; i++)
    {
        if(nodes[i] == 1){
            total++;
        }
    }
    free(nodes);

    printf("total real node = %lu\n",total);
    return 0;
}
