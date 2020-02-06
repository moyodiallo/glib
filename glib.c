#include <stdio.h>
#include <stdlib.h>

#include "glib.h"



edgelist*  make_edgelist_file(char* input, int n_of_nodes, int n_of_edges, int directed){
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
	unsigned long *d = calloc(edges->n,sizeof(unsigned long));
    adjlist* adj     = malloc(sizeof(adjlist));

	for (i=0;i<g->e;i++) {
        if(edges->directed == 0){
		    d[g->edges[i].s]++;
		    d[g->edges[i].t]++;
        }else{
            d[g->edges[i].s]++;
        }
	}

	g->cd=malloc((g->n+1)*sizeof(unsigned long));
	g->cd[0]=0;
	for (i=1;i<g->n+1;i++) {
		g->cd[i]=g->cd[i-1]+d[i-1];
		d[i-1]=0;
	}

	g->adj=malloc(2*g->e*sizeof(unsigned long));

	for (i=0;i<g->e;i++) {
		u=g->edges[i].s;
		v=g->edges[i].t;
		g->adj[ g->cd[u] + d[u]++ ]=v;
		g->adj[ g->cd[v] + d[v]++ ]=u;
	}

	free(d);
    return adj;
}

adjmatrix* make_adjmatrix_edges(edgelist* edges){
    unsigned long i,u,v;
    adjmatrix* mat = malloc(sizeof(adjmatrix));

	g->mat=calloc(g->n*g->n,sizeof(bool));
	for (i=0;i<g->e;i++){
		u=g->edges[i].s;
		v=g->edges[i].t;
		g->mat[u+g->n*v]=1;
		g->mat[v+g->n*u]=1;
	}

    return mat;
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
