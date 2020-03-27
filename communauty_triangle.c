#include <stdio.h>
#include <stdlib.h>

#include "glib.h"

int main(int argc, char** argv){
    if (argc != 5){
        printf("fail: cmd <file> <n_of_node> <n_of_edges> <p or n>");
        exit(EXIT_FAILURE);
    }

    int print;
    if(argv[4][0] == 'p')
        print = 1;
    else if(argv[4][0] == 'n')
        print = 0;
    else if(argv[4][0] == 's')
        print = 2;
    else
    {
        printf("fail: cmd <file> <n_of_node> <n_of_edges> <p or n>");
        exit(EXIT_FAILURE);
    } 

    
    char* file  = argv[1]; 
    unsigned long n_of_node = atoi(argv[2]);
    unsigned long n_of_edge = atoi(argv[3]);
    

    /*the edge list have to be directed*/
    edgelist* e_list = make_edgelist_file(file,n_of_node,n_of_edge,1);

    adjlist*  a_list = make_adjlist_edges(e_list); 
    free(e_list);

    unsigned* communaty = communauty_triangle(a_list);

    if(argv[4][0] == 'p')
    {
        for (size_t i = 1; i < a_list->n+1; i++)
        {
            if(communaty[i] != 0){
                printf("%lu  %u\n",i,communaty[i]);
            }
        }
    }

    free(a_list);
    free(communaty);
    
}
