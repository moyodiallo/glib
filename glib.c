#include <stdio.h>
#include <stdlib.h>

#include "glib.h"



edgelist*  make_edgelist_file(char* input, int n_of_nodes, int n_of_edges){
    FILE *file = fopen(input,"r");
    edgelist* g=malloc(sizeof(edgelist));
    unsigned long n = 0;

     if(file == NULL){
        printf("fail opening file");
        exit(EXIT_FAILURE);
    }

    g->n = n_of_nodes;
    g->e = n_of_edges;

    g->edges=malloc(g->e*sizeof(edge));

    while (fscanf(file,"%lu %lu",&(g->edges[n].s), &(g->edges[n].t)) == 2){
        if(n == g->n) 
        {
            printf("fail: limit of edges");
            exit(EXIT_FAILURE);
        }
        n++;
    }

    return g;
}

adjlist*   make_adjlist_edges(edgelist* edges){
    return NULL;
}

adjmatrix* make_adjmatrix_edges(edgelist* edges){
    return NULL;
}

void free_edgelist(edgelist* ed){
    if(ed != NULL){
        if(ed->edges != NULL) free(ed->edges);
        free(ed);
    }
}

void free_adjlist(adjlist* ad){
    if (ad != NULL){
        if(ad->cd  != NULL) free(ad->cd);
        if(ad->adj != NULL) free(ad->adj);
        free(ad);
    }
}

void free_adjmatrix(adjmatrix* mat){
    if(mat != NULL){
        if(mat->mat   != NULL) free(mat->mat);
        free(mat);
    }
}
