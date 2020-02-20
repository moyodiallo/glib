#include <stdio.h>
#include <stdlib.h>

#include "glib.h"

int main(int argc, char** argv){
    if (argc != 5){
        printf("fail: cmd <file> <n_of_node> <n_of_edge> <source>");
        exit(EXIT_FAILURE);
    }

    char* file  = argv[1]; 

    unsigned long n_of_node = atol(argv[2]);
    unsigned long n_of_edge = atol(argv[3]);
    unsigned long source    = atol(argv[4]);

    edgelist* e_list = make_edgelist_file(file,n_of_node,n_of_edge,0);
    adjlist*  a_list = make_adjlist_edges(e_list);  
    
    free_edgelist(e_list);

    printf("diameter %lu\n",diameter(a_list,source));

    free_adjlist(a_list);
}

