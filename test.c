#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include "glib.h"

#define NB_NODE     10
#define NB_EDGE     9
#define NB_TRIANGLE 2
#define NB_CONNEXE  3

void create_file_test(){
    FILE *f = fopen("test_data.txt", "w");
    fprintf(f,"1 2   \n");
    fprintf(f,"1 3   \n");
    fprintf(f,"2 8   \n");
    fprintf(f,"3 2   \n");
    fprintf(f,"4 5   \n");
    fprintf(f,"4 7   \n");
    fprintf(f,"5 6   \n");
    fprintf(f,"9 10  \n");
    fprintf(f,"4 6   \n");
    fclose(f);
}


int main(){
    edgelist* ed = NULL;
    create_file_test();
    ed = make_edgelist_file("test_data.txt", NB_NODE, NB_EDGE);
    for(unsigned long i=0; i<ed->e; i++){
        printf("%lu %lu\n", ed->edges[i].s, ed->edges[i].t);
    }
    free_edgelist(ed);
}
