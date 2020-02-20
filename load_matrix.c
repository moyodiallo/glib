#include <stdio.h>
#include <stdlib.h>

#include "glib.h"

int main(int argc, char** argv){
    if (argc != 4){
        printf("fail: cmd <file> <n_of_node> <n_of_edges>");
        exit(EXIT_FAILURE);
    }

    char* file  = argv[1]; 
    unsigned long n_of_node = atoi(argv[2]);
    unsigned long n_of_edge = atoi(argv[3]);

    edgelist* e_list = make_edgelist_file(file,n_of_node,n_of_edge,0);
    adjmatrix* mat      = make_adjmatrix_edges(e_list);

    free_edgelist(e_list);
    free_adjmatrix(mat);
}
