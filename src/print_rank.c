#include <stdio.h>
#include <stdlib.h>

#include "glib.h"

int main(int argc, char** argv){
    if (argc != 5){
        printf("fail: cmd <file> <n_of_node> <n_rank limit 10>");
        exit(EXIT_FAILURE);
    }

    char* file  = argv[1]; 
    unsigned long n_of_node = atoi(argv[2]);
    unsigned long n_rank    = atoi(argv[3]);

    /*the edge list have to be directed*/
    edgelist* e_list = make_edgelist_file(file,n_of_node,n_rank,1);
    adjlist*  a_list = make_adjlist_edges(e_list); 

    if(argv[4][0] == 'p')
        compute_triangle(a_list,1);
    else if(argv[4][0] == 'n')
        compute_triangle(a_list,0);
    else
    {
        printf("fail: cmd <file> <n_of_node> <n_of_edges> <p or n>");
        exit(EXIT_FAILURE);
    }    
}