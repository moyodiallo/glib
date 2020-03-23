#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#include "glib.h"

int main(int argc, char** argv){
    if (argc != 5){
        printf("fail: cmd <file> <n_of_node> <n_of_edges> <p or n>");
        exit(EXIT_FAILURE);
    }

    unsigned long i;
    
    char* file  = argv[1]; 

    unsigned long core,prefix_size;

    unsigned long n_of_node = atoi(argv[2]);
    unsigned long n_of_edge = atoi(argv[3]);

    unsigned long* n_deg      = calloc(n_of_node+1,sizeof(unsigned long));
    unsigned long* node_core  = calloc(n_of_node+1,sizeof(unsigned long));
    unsigned long* pref_node  = calloc(n_of_node+1,sizeof(unsigned long));

    edgelist* e_list = make_edgelist_file(file,n_of_node,n_of_edge,0);
    adjlist*  a_list = make_adjlist_edges(e_list);

    for (i = 0; i < e_list->e; i++)
    {
        n_deg[e_list->edges[i].s]++;
        n_deg[e_list->edges[i].t]++;

    }


    free_edgelist(e_list);
    core = kcore(a_list,n_deg,node_core,pref_node,&prefix_size);
    free(n_deg);     

    if(argv[4][0] == 'p'){
       for (i = 1; i < n_of_node+1; i++)
       {
           if(node_core[i] != 0){
               printf("%lu %lu\n",i,node_core[i]);
           }
       }  
    }

    if(argv[4][0] == 'n'){
        printf("core max %lu\n",core);
        denset_subgraph(a_list,pref_node,prefix_size);
    }

    free(pref_node);
    free(node_core);
    free_adjlist(a_list);
}
