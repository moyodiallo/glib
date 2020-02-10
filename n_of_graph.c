#include <stdio.h>
#include <stdlib.h>

#include "glib.h"

int main(int argc, char** argv){
    if(argc < 2){
        printf("fail: cmd <file>");
        exit(EXIT_FAILURE);
    }
    print_n_of_graph(argv[1]);
    return 0;
}
