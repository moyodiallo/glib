#include <stdio.h>
#include <stdlib.h>

#include "glib.h"

int main(int argc, char** argv){
    if (argc != 4){
        printf("fail: cmd <file> <n_of_node> <n_of_edges>");
        exit(EXIT_FAILURE);
    }
    unsigned long n_of_edge,n_of_node;
    n_of_node = atol(argv[2]);
    n_of_edge = atol(argv[3]);
    edgelist* ed = make_edgelist_file(argv[1], n_of_node, n_of_edge,0);
    direct_by_deg(ed);
    print_edgelsit(ed);
}
