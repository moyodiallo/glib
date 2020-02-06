#include <stdio.h>
#include <stdlib.h>

#include "glib.h"


edgelist*  make_edgelist_file(char* input, int n_of_nodes, int n_of_edges, char directed){
    FILE *file  = fopen(input,"r");
    edgelist* g = malloc(sizeof(edgelist));
    unsigned long n = 0;
    g->directed = directed;

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

adjlist*   make_adjlist_edges(edgelist* e_list){
    unsigned long i,u,v;
	unsigned long *d  = calloc(e_list->n,sizeof(unsigned long));
    adjlist* adj_list = malloc(sizeof(adjlist));

	for (i=0;i<e_list->e;i++) {
        if(e_list->directed == 0){
		    d[e_list->edges[i].s]++;
		    d[e_list->edges[i].t]++;
        }else{
            d[e_list->edges[i].s]++;
        }
	}

	adj_list->cd    = malloc((e_list->n+1)*sizeof(unsigned long));
	adj_list->cd[0] = 0;
	for (i=1;i<e_list->n+1;i++) {
		adj_list->cd[i]=adj_list->cd[i-1]+d[i-1];
		d[i-1]=0;
	}

	adj_list->adj=malloc(2*e_list->e*sizeof(unsigned long));
	for (i=0;i<e_list->e;i++) {
		u = e_list->edges[i].s;
		v = e_list->edges[i].t;
		adj_list->adj[ adj_list->cd[u] + d[u]++ ] = v;
		adj_list->adj[ adj_list->cd[v] + d[v]++ ] = u;
	}

	free(d);
    return adj_list;
}

adjmatrix* make_adjmatrix_edges(edgelist* e_list){
    unsigned long i,u,v;
    adjmatrix* adj_mat = malloc(sizeof(adjmatrix));
	adj_mat->mat = calloc(e_list->n*e_list->n,sizeof(char));

	for (i=0;i<e_list->e;i++){

		u = e_list->edges[i].s;
		v = e_list->edges[i].t;

        if(e_list->directed == 0){
		    adj_mat->mat[u + adj_mat->n * v] = 1;
		    adj_mat->mat[v + adj_mat->n * u] = 1;
        }else
        {
            adj_mat->mat[u + adj_mat->n * v] = 1;
        }   
	}
    return adj_mat;
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
