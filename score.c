#include <stdio.h>
#include <stdlib.h>

#include "glib.h"

int main(int argc, char** argv){
    
    if (argc != 6){
        printf("fail: cmd <file> <n_of_node> <n_of_edges> <times> <p or n>");
        exit(EXIT_FAILURE);
    }

    unsigned long i;
    
    char* file  = argv[1];

    unsigned long n_of_node = atoi(argv[2]);
    unsigned long n_of_edge = atoi(argv[3]);

    int times = atoi(argv[4]);

    edgelist* e_list = make_edgelist_file(file,n_of_node,n_of_edge,0);

    double* score = density_score(e_list,times);

    if(argv[5][0] == 'p'){
        for (i = 1; i < n_of_node+1; i++)
        {
            printf("%lu %f\n",i,score[i]);
        }
    }
}
