#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "glib.h"

void print_edgelsit(edgelist* e_list){
    unsigned long i ;
    for (i= 0; i < e_list->e; i++)
    {
        if(e_list->edges[i].s != 0){
            printf("%lu %lu\n",e_list->edges[i].s,e_list->edges[i].t);
        }
    }
}

void print_adjlist(adjlist* adj_list){
    unsigned long i,j;
    for (i = 1; i < adj_list->n; i++)
    {
        printf("%lu : ",i);
        for (j = adj_list->cd[i-1]; j < adj_list->cd[i]; j++)
        {
            printf("%lu ",adj_list->adj[j]);   
        }
        printf("\n"); 
    }
    
}

void print_n_of_graph(char* input){
    couple c = n_of_graph(input);
    printf("n_of_node: %lu\nn_of_edge: %lu\n",c.x,c.y);
}

couple n_of_graph(char* input){
    couple c;
    unsigned long u,v;
    unsigned long n_of_edges = 0;
    unsigned long n_of_nodes = 0;
    FILE *file  = fopen(input,"r");

     while (fscanf(file,"%lu %lu",&u, &v) == 2){
        n_of_edges++;
        if(u > v && u > n_of_nodes){
            n_of_nodes = u;
        }else if(v > u && v > n_of_nodes){
            n_of_nodes = v;
        }
     }

    c.x = n_of_nodes;
    c.y = n_of_edges;
    return c;
}

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
        if(n == g->e) 
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
	unsigned long *deg  = calloc(e_list->n+1,sizeof(unsigned long));
    adjlist* adj_list   = malloc(sizeof(adjlist));

    adj_list->e = e_list->e;
    adj_list->n = e_list->n;
    adj_list->directed = e_list->directed;

	for (i=0;i<e_list->e;i++) {
        if(e_list->directed == 0){
		    deg[e_list->edges[i].s]++;
		    deg[e_list->edges[i].t]++;
        }else{
            deg[e_list->edges[i].s]++;
        }
	}

	adj_list->cd    = malloc((e_list->n+1)*sizeof(unsigned long));
	adj_list->cd[0] = 0;
	for (i=1;i<e_list->n+1; i++) {
		adj_list->cd[i] = adj_list->cd[i-1]+deg[i];
		deg[i] = 0;
	}

	if(e_list->directed == 0) {
        adj_list->adj = malloc(2*e_list->e*sizeof(unsigned long));
    }else {
        adj_list->adj = malloc(e_list->e*sizeof(unsigned long));
    }

	for (i=0; i < e_list->e; i++) {
		u = e_list->edges[i].s;
		v = e_list->edges[i].t;

        if(e_list->directed == 0){
		    adj_list->adj[ adj_list->cd[u-1] + deg[u]++ ] = v;
		    adj_list->adj[ adj_list->cd[v-1] + deg[v]++ ] = u;
        }else {
            adj_list->adj[ adj_list->cd[u-1] + deg[u]++ ] = v;
        }
	}

	free(deg);
    return adj_list;
}

adjmatrix* make_adjmatrix_edges(edgelist* e_list){
    unsigned long i,u,v;
    adjmatrix* adj_mat = malloc(sizeof(adjmatrix));
	adj_mat->mat = calloc(e_list->n*e_list->n,sizeof(char));

    adj_mat->e = e_list->e;
    adj_mat->n = e_list->n;
    adj_mat->directed = e_list->directed;

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

void generate4clusters(unsigned long n_of_nodes, double p, double q){
    unsigned long i,j,n;
    char* clusters = malloc(sizeof(char)*(n_of_nodes+1));
    double r;

    n = 1;
    j = 0;
    /*giving the node's cluster id */
    for (i = 1; i < n_of_nodes+1; i++)
    {
        clusters[i] = n;
        j++;
        if(j == 100){
            j = 0;
            n++;
        }
    }

    /*making the links*/
     srand(time(0));
    for (i = 1; i < n_of_nodes+1; i++)
    {
        for ( j = i; j < n_of_nodes+1; j++)
        {
            r = ((double)rand() / (double)((unsigned)RAND_MAX + 1));
            if ( r <= p && clusters[i] == clusters[j] ){
                printf("%lu %lu\n",i,j);
            }else if( r <= q && clusters[i] != clusters[j] ){
                printf("%lu %lu\n",i,j);
            }
        }  
    }
    
}

int random_int(int min, int max)
{
   return min + rand() % (max+1 - min);
}

void shuffle_random(unsigned long* vector, unsigned long size){
    unsigned long i,t;
    srand(time(0));
    for (i = 1; i < size; i++){
        int n = random_int(i+1,size);
        t     = vector[n];
        vector[n] = vector[i];
        vector[i] = t;
    }
}

unsigned long* label_propagation(adjlist* adj_list, int times){
    int change;
    unsigned long i,j,t,node,max,n,ng;
    unsigned long* lb = malloc((adj_list->n+1)*sizeof(unsigned long));
    unsigned long *cu = malloc((adj_list->n+1)*sizeof(unsigned long));
    unsigned long *nd = malloc((adj_list->n+1)*sizeof(unsigned long));

    for (i = 1; i < adj_list->n+1; i++){
        if(n_of_neighbor(adj_list,i) != 0){
            lb[i] = i;
            nd[i] = i;
        }else{
            lb[i] = 0;
            nd[i] = 0;
        }
    }


    change = 1;
    for (i = 0; i < (unsigned long)times; i++){
        shuffle_random(nd,adj_list->n);

        /*
        for (i=1; i < adj_list->n+1; i++)
        {
            printf("%lu\n", nd[i]);
        }
        exit(EXIT_FAILURE);
        */
        
        for ( j = 1; j < adj_list->n+1; j++){
            node  = 0;
            max   = 0;
            n     = nd[j]; /*the node shuffled*/
            

            if(n == 0) continue; /*this node have not to exist*/

            cu[lb[n]] = 0; /*for counting label localy*/
            for (t = adj_list->cd[n-1]; t < adj_list->cd[n]; t++){
                ng = adj_list->adj[t];
                cu[ lb[ng] ] = 0;
            }

            for (t = adj_list->cd[n-1]; t < adj_list->cd[n]; t++){
                ng = adj_list->adj[t];
                cu[ lb[ng] ]++;
            }

            cu[ lb[n] ]++;

            /* search most neighbour-hood*/
            for (t = adj_list->cd[n-1]; t < adj_list->cd[n]; t++){
                ng = adj_list->adj[t];
                if(cu[ lb[ng] ] > max){
                    max  = cu[ lb[ng] ];  /*max label amount neighbours*/
                    node = ng;            /*node choosed*/
                }
            }

            if(node == 0){
                continue;
            }
            
            if(cu[ lb[node] ] == cu[ lb[n] ]){
                lb[n] = lb[node];
            }else if( cu[ lb[node] ] > cu[ lb[n] ]){
                lb[n] = lb[node];
            }
        }
    }
    free(cu);
    free(nd);
    return lb;
}

unsigned long n_of_neighbor(adjlist* a_list, unsigned long n){
    return a_list->cd[n] - a_list->cd[n-1];
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
        if(mat->mat != NULL) free(mat->mat);
        free(mat);
    }
}

fifo* make_fifo(unsigned long size){
    fifo* f   = malloc(sizeof(fifo));
    f->size   = size+1;
    f->i      = 0;
    f->j      = 0;
    f->value = malloc((size+1)*sizeof(unsigned long));
    return f;
}

int is_full_fifo(fifo* f){
    if(f->j == (f->i +1) % f->size)
        return 1;
    else 
        return 0;
}

unsigned long pop_fifo(fifo* f){
    unsigned long p;
    if(f->j == f->i) return 0;
    p = f->value[f->j];
    f->j++;
    f->j = f->j % f->size;
    return p;
}

void push_fifo(fifo* f, unsigned long val){
    if(is_full_fifo(f) == 1){
        printf("fail: fifo is full\n");
        exit(EXIT_FAILURE);
    }
    f->value[f->i] = val;
    f->i++;
    f->i = f->i % f->size;
}

void free_fifo(fifo* f){
    free(f->value);
    free(f);
}

void direct_by_deg(edgelist* e_list){
    unsigned long i,n;
    unsigned long* d = calloc(e_list->n+1,sizeof(unsigned long));
    for (i = 0; i < e_list->e; i++){
        d[e_list->edges[i].s]++;
        d[e_list->edges[i].t]++;
    }

    for (i = 0; i < e_list->e; i++){
        if( d[e_list->edges[i].s] > d[e_list->edges[i].t])
        {
            n = e_list->edges[i].s;
            e_list->edges[i].s = e_list->edges[i].t;
            e_list->edges[i].t = n;
        }else if( d[e_list->edges[i].s] ==  d[e_list->edges[i].t])
        {
            if(e_list->edges[i].s > e_list->edges[i].t){
                n = e_list->edges[i].s;
                e_list->edges[i].s = e_list->edges[i].t;
                e_list->edges[i].t = n;
            }
        }
    }
}

unsigned long compute_triangle(adjlist* adj_list, int status){
    unsigned long i,j,count,i_1,i_2,l_1,l_2;
    triangle tri;
    count = 0;
    for (i = 1; i < adj_list->n; i++)
    {
        /*find triangle*/
        for (j = adj_list->cd[i-1]; j < adj_list->cd[i]; j++)
        {
            tri.p_1 = i;
            tri.p_2 = adj_list->adj[j];

            if(n_of_neighbor(adj_list,tri.p_2) == 0) continue;

            /*find third node*/
            i_1 = adj_list->cd[tri.p_1-1];
            i_2 = adj_list->cd[tri.p_2-1];

            l_1 = adj_list->cd[tri.p_1];
            l_2 = adj_list->cd[tri.p_2];

            while (i_1 < l_1 && i_2 < l_2)
            {
                /*printf(" -> %lu %lu %lu %lu\n",tri.p_1, tri.p_2, adj_list->adj[i_1], adj_list->adj[i_2]);*/
                if(adj_list->adj[i_1] < adj_list->adj[i_2]){
                    i_1++;
                }else if(adj_list->adj[i_1] > adj_list->adj[i_2]){
                    i_2++;
                }else if(adj_list->adj[i_1] == adj_list->adj[i_2]){
                    tri.p_3 = adj_list->adj[i_1];
                    i_1++;
                    i_2++;
                    count++;
                    if(status){
                        printf("%lu %lu %lu\n",tri.p_1, tri.p_2, tri.p_3);
                    }
                }
            }
        }      
    }
    return count;
}

unsigned long* connected(adjlist* adj_list, int print){

}

