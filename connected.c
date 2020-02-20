#include <stdio.h>
#include <stdlib.h>

#include "glib.h"

int main(int argc, char** argv){
    if (argc != 5){
        printf("fail: cmd <file> <n_of_node> <n_of_edge> <p or s or m>");
        exit(EXIT_FAILURE);
    }

    int print;
    if(argv[4][0] == 'p'){
        print = 1;
    }else if(argv[4][0] == 's'){
        print = 2;
    }else if(argv[4][0] == 'm'){
        print = 3;
    }else
    {
         printf("fail: cmd <file> <n_of_node> <n_of_edge> <p or s or m>");
         exit(EXIT_FAILURE);
    }

    char* file  = argv[1]; 

    unsigned long n_of_node = atol(argv[2]);
    unsigned long n_of_edge = atol(argv[3]);

    edgelist* e_list = make_edgelist_file(file,n_of_node,n_of_edge,0);
    adjlist*  a_list = make_adjlist_edges(e_list);  
    
    free_edgelist(e_list);

    connected(a_list,print);
    
    free_adjlist(a_list);
}

