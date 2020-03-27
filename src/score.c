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

    unsigned long prefix_size;
    unsigned long *prefix_order;
    double* score = density_score(e_list,times,&prefix_size,&prefix_order);

    if(argv[5][0] == 'p'){
        for (i = 1; i < n_of_node+1; i++)
        {
            printf("%lu %f\n",i,score[i]);
        }
    }

    double max_score = 0;
    for (size_t i = 1; i < n_of_node+1; i++)
    {
        if(score[i] > max_score)
        {
            max_score = score[i];
        }
    }
    

    free(score);
    adjlist *a_list = make_adjlist_edges(e_list);
    free_edgelist(e_list);

    if(argv[5][0] == 'n'){
        printf("score max density = %f\n",max_score);
        denset_subgraph(a_list,prefix_order,prefix_size);
    }

    free(prefix_order);
    free_adjlist(a_list);
}
