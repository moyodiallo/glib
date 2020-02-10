#include <stdio.h>
#include <stdlib.h>

#include "glib.h"

int main(int argc, char** argv){
    if (argc != 6){
        printf("fail: cmd <times> <file> <n_of_node> <n_of_edges> <p or n>");
        exit(EXIT_FAILURE);
    }

    unsigned long i;
    int times   = atoi(argv[1]);
    char* file  = argv[2]; 

    unsigned long n_of_node = atoi(argv[3]);
    unsigned long n_of_edge = atoi(argv[4]);

    edgelist* e_list = make_edgelist_file(file,n_of_node,n_of_edge,0);
    adjlist*  a_list = make_adjlist_edges(e_list);    

    unsigned long* lb =  label_propagation(a_list,times);

    if(argv[5][0] == 'p'){
        for(i= 1; i<e_list->n+1; i++){
            if( n_of_neighbor(a_list,i) != 0 ){
                printf("%lu %lu\n", i, lb[i]);
            }
        }
    }

   free(lb);
   free_adjlist(a_list);
   free_edgelist(e_list);
}
