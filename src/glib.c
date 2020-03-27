#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <limits.h>

#include "glib.h"

//#define DEBUG

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
            printf("fail: limit of edges %lu\n",n);
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
	adj_mat->mat = calloc((e_list->n+1)*(e_list->n+1),sizeof(char));

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

void generate_clusters(unsigned long n_of_nodes, unsigned long n_of_cluster, double p, double q){
    unsigned long i,j,n,n_per_cluster;
    char* clusters = malloc(sizeof(char)*(n_of_nodes+1));
    double r;

    n = 1;
    j = 0;
    n_per_cluster = n_of_nodes / n_of_cluster;
    /*giving the node's cluster id */
    for (i = 1; i < n_of_nodes+1; i++)
    {
        clusters[i] = n;
        j++;
        if(j == n_per_cluster){
            j = 0;
            n++;
        }
    }

    /*making the links*/
     srand(time(0));
    for (i = 1; i < n_of_nodes+1; i++)
    {
        for ( j = i+1; j < n_of_nodes+1; j++)
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

unsigned long* label_propagation(adjlist* adj_list, int times,int* limit){
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

    for (i = 0; i < (unsigned long)times; i++){
        shuffle_random(nd,adj_list->n);

        change  = 0;
        
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
                change = 1;
            }else if( cu[ lb[node] ] > cu[ lb[n] ]){
                lb[n] = lb[node];
                change = 1;
            }
        }

        if(change == 0){
            free(cu);
            free(nd);
            *limit = i+1;
            return lb;
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

int is_empty_fifo(fifo* f){
    if(f->i == f->j) 
        return 1;
    else 
        return 0;
}

unsigned long pop_fifo(fifo* f){
    unsigned long p;
    if(is_empty_fifo(f) == 1){
        printf("fail: fifo is empty");
        exit(EXIT_FAILURE);
    }
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

unsigned long compute_triangle(adjlist* adj_list,unsigned long* belongs, int status){
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
                    if(status == 1){
                        printf("%lu %lu %lu\n",tri.p_1, tri.p_2, tri.p_3);
                    }

                    belongs[tri.p_1]++;
                    belongs[tri.p_2]++;
                    belongs[tri.p_3]++;
                }
            }
        }      
    }
    return count;
}

unsigned long bfs(adjlist* adj_list, unsigned long s, unsigned long* mark, unsigned long color, int print){
    unsigned long j,ng, size;
    fifo* f = make_fifo(adj_list->n);

    push_fifo(f,s);
    mark[s] = color;
    size     = 0;
    while (is_empty_fifo(f) == 0)
    {
        unsigned long n = pop_fifo(f);
        size += 1;
        if(print == 1){
            printf("%lu ",n);
        }
        for (j = adj_list->cd[n-1]; j < adj_list->cd[n]; j++){

            ng = adj_list->adj[j];
            if(mark[ng] == 0){
                mark[ng]  = color;
                push_fifo(f,ng);
            }
        }
    }

    free_fifo(f);
    return size;
}

void connected(adjlist* adj_list, int print){
    unsigned long i, color, size, max, node;
    unsigned long* mark  = calloc(adj_list->n+1,sizeof(unsigned long)); 

    color = 0;
    max = 0;
    for (i = 1; i < adj_list->n+1; i++)
    {
        if(mark[i] == 0 && n_of_neighbor(adj_list,i) > 0){
            color++;
            size = bfs(adj_list,i,mark,color,print);
            if(print == 1){
                printf("\n");
            }
            if(print == 2){
                printf("%lu %lu\n",color,size);
            }  
        }

        if(max < size) {
            max  = size;
            node = i;
        }
    }

    if(print == 3){
        printf("size=%lu\nnode=%lu\ntotal=%lu\n",max,node,color);
    }

    free(mark);
}

couple bfs2(adjlist* adj_list, unsigned long s){
    unsigned long j, ng, n;
    fifo* f = make_fifo(adj_list->n);
    unsigned long* mark  = calloc(adj_list->n+1,sizeof(unsigned long));
    unsigned long* level = malloc((adj_list->n+1)*sizeof(unsigned long));
    couple cp;

    push_fifo(f,s);
    mark[s]  = 1;
    level[s] = 0;
    while (is_empty_fifo(f) == 0)
    {
        n = pop_fifo(f);
        for (j = adj_list->cd[n-1]; j < adj_list->cd[n]; j++){
            ng = adj_list->adj[j];
            if(mark[ng] == 0){
                mark[ng] = 1;
                push_fifo(f,ng);
                level[ng] = level[n] + 1; 
            }
        }
    }    

    cp.x = level[n];
    cp.y = n;

    free(mark);
    free_fifo(f);
    free(level);
    return cp;
}

unsigned long diameter(adjlist* adj_list, unsigned long s){
    couple cp;
    unsigned long i;
    unsigned long diam = 0;
    unsigned long node = s;

    for (i = 0; i < 10; i++)
    { 
        cp = bfs2(adj_list,node);
        if(diam < cp.x){
            node = cp.y;
            diam = cp.x;
        }else if(node == cp.y){
            break;
        }
    }
    return diam;
}

double* page_rank(edgelist* e_list_direct, double alpha, unsigned theta, int trace){
    unsigned long i,j;
    unsigned long nodes = 0;
    double som, P_1;

    double *T, *P, *P_N;
    unsigned long* d_out;
    char* exist;

    /*printf("dout\n");*/
    /*calcul D_out*/
    d_out = calloc(e_list_direct->n+1,sizeof(unsigned long));
    exist = calloc(e_list_direct->n+1,sizeof(char));
    

    for (i = 0; i < e_list_direct->e; i++)
    {
        d_out[e_list_direct->edges[i].s]++;
        exist[e_list_direct->edges[i].s] = 1;
        exist[e_list_direct->edges[i].t] = 1;
    }

    /*printf("count node\n");*/
    /*count nodes*/
    for (i = 1; i < e_list_direct->n+1; i++)
    {
        if(exist[i] != 0){
            nodes++;
        }
    }
    /*free(exist)*/;

    /*printf("matrix\n");*/
    /* transition matrix */
    T = calloc(e_list_direct->e,sizeof(double));
    for (j = 0; j < e_list_direct->e; j++)
    {
        if(d_out[e_list_direct->edges[j].s] != 0){
            T[j] = 1.0/(d_out[e_list_direct->edges[j].s]);
        }else
        {
            T[j] = 1.0/(nodes);
        }
    }
    free(d_out);

    /*printf("P initialize\n");*/
    /*intitalize P*/
    P = malloc((e_list_direct->n+1)*sizeof(double));
    for (i = 1; i < e_list_direct->n+1; i++)
    {
        if(exist[i] == 1)
            P[i] = 1.0/(nodes);
        else
            P[i] = 0.0;
    }
    free(exist);

    /*printf("Ranking\n");*/
    /*Ranking*/
    for (j = 0; j < theta; j++){

        P_N = P;
        P   = prod_mat_vect3(e_list_direct,T,P);
        P_1 = 0.0;
        for (i = 1; i < e_list_direct->n+1; i++){
            if(P[i] != 0){
                P[i] = ((1-alpha)*P[i]) + (alpha/(nodes));
                P_1  = P_1 + P[i];
            }
        }
        normalize2(P,nodes,e_list_direct->n,P_1);

        som = 0.0;
        for (i = 0; i < e_list_direct->n+1; i++){
            som += P[i];
        }
        
        /*
        if(trace == 1){
            if(equals_P(P,P_N,e_list_direct->n) == 1){
                printf("STABLE AT %lu AND TOTAL RANK %f\n",j,som);
                free(P_N);
                break;
            }else{
                free(P_N);
            }
        }
        */
        
    }

    /*
    printf("finish\n");
    for (i = 1; i < 20; i++)
    {
        if(((P[i]*100)) != ((P_N[i]*100)))
            printf("N %lu %lf %lf\n",i,P[i]*100,P_N[i]*100);
        else 
            printf("Y %lu %lf %lf\n",i,P[i]*100,P_N[i]*100);

    }
    */

   /*
   printf("variation error %lf\n",P[3]);
   unsigned long node;
   double max;
   if(trace == 1){
        for ( j = 0; j < 20; j++)
        {
            max = 0;

            for (i = 1; i < e_list_direct->n+1; i++)
            {
                if(max < P[i]){
                    node = i;
                    max  = P[i]; 
                }
            }
            
            printf("rank %lu %lf %lf\n",node,P[node], P[node] - P_N[node]);
            P[node] = 0;
        }
    }
    */

    

    if(trace == 1) printf("iterations: %lu | total rank %f\n",j,som*100);
    return P;
}


void normalize2(double* P, unsigned long nodes, unsigned long size, double P_1){
    unsigned long i;
    for (i = 1; i < size+1; i++){
        if(P[i] != 0)
            P[i] = P[i] + ((1 - P_1)/(nodes));
    }
}

int equals_P(double* P, double* P_N, unsigned long n){
    unsigned long i;
    for (i = 1; i < n+1; i++){
        if(P[i] != 0){
            if(P[i] != P_N[i]){
                    return 0;
            }
        }
    }
    return 1;
}


double* prod_mat_vect3(edgelist* e_list, double* T, double* P){
    unsigned long i;

    double* B = calloc(e_list->n+1,sizeof(double*));

    for (i = 0; i < e_list->e; i++){
        B[e_list->edges[i].t] += (T[i] * P[e_list->edges[i].s]);
    }
    return B;
}


heap* make_heap(unsigned long size){
    heap* h = malloc(sizeof(heap));
    h->size  = size;
    h->index = 0;
    h->value = malloc(h->size*sizeof(unsigned long));
    return h;
}

void free_heap(heap* h){
    if(h != NULL){
        if(h->value != NULL) free(h->value);
        free(h);
    }
}

void push_heap(heap* h, unsigned long* deg, unsigned long node, unsigned long* position){
    if(h->index == h->size){
        printf("fail: heap is full\n");
        exit(EXIT_FAILURE);
    }

    h->value[h->index] = node;
    position[h->value[h->index]] = h->index;
    up_heap(h,deg,h->index,position);
    h->index++;
}

unsigned long pop_heap(heap* h, unsigned long* deg, unsigned long* position){
    unsigned long p = h->value[0];

    if(h->index == 0){
        printf("fail: heap is empty\n");
        exit(EXIT_FAILURE);
    }

    h->value[0]  = h->value[h->index-1];
    position[h->value[h->index-1]] = 0;
    h->index--;
    down_heap(h,deg,0,position);

    return p;
}

void exchange(unsigned long* value,unsigned long index_1, unsigned long index_2){
    unsigned long tmp;
    tmp            = value[index_1];
    value[index_1] = value[index_2];
    value[index_2] = tmp;
}

void up_heap(heap* h, unsigned long* deg, unsigned long index,unsigned long* position){

    if(index == 0){
        return;
    }

    unsigned long father = (index-1)/2;

    if(deg[h->value[index]] < deg[h->value[father]]){

        exchange(h->value,index,father);
        exchange(position,h->value[index],h->value[father]);

        up_heap(h,deg,father,position);
    }
}


void down_heap(heap* h, unsigned long* deg, unsigned long index, unsigned long* position){
    unsigned long smallest = index;
    unsigned long left     = 2*smallest+1;
    unsigned long right    = 2*smallest+2;

    if(right < h->index && deg[h->value[right]] < deg[h->value[smallest]]){
        smallest = right;
    }

    if(left < h->index && deg[h->value[left]] < deg[h->value[smallest]]){
        smallest = left;
    }

    if(smallest != index){
        exchange(h->value,smallest,index);
        exchange(position, h->value[smallest],h->value[index]);

        down_heap(h,deg,smallest,position);
    }
}

void max_heapfy(heap* h, unsigned long* deg, unsigned long* position, unsigned long i){
    unsigned long left     = 2*i+1;
    unsigned long right    = 2*i+2;
    unsigned long largest  = i;

    if(left < h->index && deg[h->value[left]] < deg[h->value[largest]]){
        largest = left;
    }

    if(right < h->index && deg[h->value[right]] < deg[h->value[largest]]){
        largest = right;
    }

    if(largest != i){
        exchange(h->value,largest,i);
        exchange(position,h->value[largest],h->value[i]);
        max_heapfy(h,deg,position,largest);
    }
}

void percolate(heap* h, unsigned long* deg, unsigned long* position)
{
    unsigned long i = h->index/2;
    //unsigned long node_val,father,father_val;

    while (i > 0)
    {   
        max_heapfy(h,deg,position,i);
        i--;
    }
    max_heapfy(h,deg,position,0);
}


unsigned long kcore(adjlist* a_list , unsigned long* n_deg, 
    unsigned long *core_node, unsigned long *prefix_node, unsigned long *pref_size)
{
    unsigned long prefix = 0;
    unsigned long core   = 0;
    unsigned long node,ng;
    unsigned long* position;

    //unsigned long max_deg = 0;

    char* mark = calloc(a_list->n+1,sizeof(char));

    heap h;
    h.value  = calloc(a_list->n,sizeof(unsigned long));
    position = calloc(a_list->n+1,sizeof(unsigned long)); /*store all position in value*/
    h.index  = 0;

    for (size_t j = 0; j < a_list->n; j++)
    {
        if(n_deg[j+1] != 0)
        {
            prefix++;
            h.value[h.index++] = j+1;
        }
    }

    *pref_size = prefix;

    for (size_t i = 0; i < h.index; i++)
    {
        position[h.value[i]] = i;
    }
    
    percolate(&h,n_deg,position); //make heap

    while (h.index != 0)
    {
        node = pop_heap(&h,n_deg,position);
       
        if(core < n_deg[node]){
            core = n_deg[node];
        }
        
        prefix--;
        core_node[node]      = core;
        prefix_node[prefix]  = node;
        mark[node]           = 1; 

        for (size_t j = a_list->cd[node-1]; j < a_list->cd[node]; j++)
        {
            ng = a_list->adj[j];
             
            if(mark[ng] != 1)
            {
                n_deg[ng]--;
                up_heap(&h,n_deg,position[ng],position);
            }
        }
    }       

    free(h.value);
    return core;
}

void denset_subgraph(adjlist* a_list, unsigned long* prefix_node, unsigned long prefix_size)
{
    unsigned long node;
    unsigned long number_nodes = 0;
    unsigned long number_edges = 0;
 
    double edge_density         = 0.0;
    double average_degree       = 0.0;
    unsigned long denset_size   = 0;

    double max_edge_density         = 0.0;
    double max_average_degree       = 0.0;
    unsigned long max_denset_size   = 0;



    char* marked = calloc(a_list->n+1,sizeof(char));

    for (size_t i = 0; i < prefix_size; i++)
    {   
            node         = prefix_node[i];
            marked[node] = 1;
            number_nodes++;

            for (size_t j = a_list->cd[node-1]; j < a_list->cd[node]; j++)
            {
                if(marked[a_list->adj[j]] == 1)
                {
                    number_edges++;
                }
            }

            edge_density    = ((double)number_edges) / ((double)(number_nodes*(number_nodes-1))/2.0);
            average_degree  = ((double)number_edges) / (double)(number_nodes);
            denset_size     = number_edges;

           if(max_average_degree < average_degree && max_denset_size < denset_size)
           {
               max_average_degree = average_degree;
               max_denset_size     = denset_size;
               max_edge_density    = edge_density;
           }
    }

    printf("denset graph:\n");
    printf("    average degree density  = %f\n",max_average_degree/2.0);
    printf("    edges density           = %f\n",max_edge_density);
    printf("    denset size             = %lu\n",max_denset_size);

    free(marked);
}

double* density_score(edgelist *e_list, int times, unsigned long *pref_size, unsigned long **pref_order)
{
    double* score_t = calloc((e_list->n+1),sizeof(double));

    unsigned long prefix = 0;

    for (size_t i = 0; i < (size_t)times; i++)
    {
        for (size_t j = 0; j < e_list->e; j++)
        {
            if(score_t[e_list->edges[j].s] <= score_t[e_list->edges[j].t]){
                score_t[e_list->edges[j].s]++;
            }else
            {
                score_t[e_list->edges[j].t]++;
            }
        }
    }

    for (size_t i = 1; i < e_list->n+1; i++)
    {
        if(score_t[i] != 0){
            score_t[i] = score_t[i] / (double)times;
            prefix++;
        }
    }
   

    //prefix order
    unsigned long *prefix_order = malloc(prefix*sizeof(unsigned long));

    
    //prepare for sort
    heap *prefix_heap              = make_heap(prefix);
    unsigned long *prefix_position = calloc((e_list->n+1),sizeof(unsigned long));
    double *score_deg              = score_t;

    //heap value
    for (size_t i = 1; i < e_list->n+1; i++)
    {   
        if(score_deg[i] != 0){
            prefix_heap->value[prefix_heap->index++] = i;
        }
    }

    //heap position
    for (size_t i = 0; i < prefix; i++)
    {
        prefix_position[prefix_heap->value[i]] = i;
    }

    percolate_degDouble(prefix_heap,score_deg,prefix_position);
    for (size_t i = 0; i < prefix; i++)
    {
        unsigned long          v = pop_heap_degDouble(prefix_heap,score_deg,prefix_position);
        prefix_order[prefix-i-1] = v;
    }
    
    *pref_size = prefix;
    *pref_order = prefix_order;

    #ifdef DEBUG 
    for (size_t i = 0; i < prefix; i++)
    {
        printf("prefix %lu\n",prefix_order[i]);
    }
    
    #endif


    free(prefix_position);
    free_heap(prefix_heap);
    return score_t;
}

unsigned* communauty_triangle(adjlist* adj_list){

    unsigned * communauty = calloc(adj_list->n+1,sizeof(unsigned));
    //unsigned color        = 1;

    unsigned long i_1,i_2,l_1,l_2;
    triangle tri;

    for (size_t i = 1; i < adj_list->n+1; i++)
    {
        if(n_of_neighbor(adj_list,i) != 0){
            communauty[i] = i;
        }else
        {
            communauty[i] = 0;
        }
        
    }

    for (size_t i = 1; i < adj_list->n; i++)
    {
        /*find triangle*/
        for (size_t j = adj_list->cd[i-1]; j < adj_list->cd[i]; j++)
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

                    if(communauty[tri.p_1] != 0 && communauty[tri.p_1] == communauty[tri.p_2])
                    {
                        communauty[tri.p_3] = communauty[tri.p_1];

                    }else if(communauty[tri.p_1] != 0 && communauty[tri.p_1] == communauty[tri.p_3])
                    {
                        communauty[tri.p_2] = communauty[tri.p_1];

                    }else if(communauty[tri.p_2] != 0 && communauty[tri.p_3] == communauty[tri.p_2])
                    {
                        communauty[tri.p_1] = communauty[tri.p_2];

                    }else
                    {
                        communauty[tri.p_1] = communauty[tri.p_2];
                        communauty[tri.p_3] = communauty[tri.p_1];
                    }
                }
            }
        }      
    }
    return communauty;
}

void down_heap_degDouble(heap* h, double* deg, unsigned long index, unsigned long* position){
    unsigned long smallest = index;
    unsigned long left     = 2*smallest+1;
    unsigned long right    = 2*smallest+2;

    if(right < h->index && deg[h->value[right]] < deg[h->value[smallest]]){
        smallest = right;
    }

    if(left < h->index && deg[h->value[left]] < deg[h->value[smallest]]){
        smallest = left;
    }

    if(smallest != index){
        exchange(h->value,smallest,index);
        exchange(position, h->value[smallest],h->value[index]);

        down_heap_degDouble(h,deg,smallest,position);
    }
}

void percolate_degDouble(heap* h, double* deg, unsigned long* position)
{
    unsigned long i = h->index/2;
    //unsigned long node_val,father,father_val;

    while (i > 0)
    {   
        max_heapfy_degDouble(h,deg,position,i);
        i--;
    }
    max_heapfy_degDouble(h,deg,position,0);
}

void max_heapfy_degDouble(heap* h, double* deg, unsigned long* position, unsigned long i){
    unsigned long left     = 2*i+1;
    unsigned long right    = 2*i+2;
    unsigned long largest  = i;

    if(left < h->index && deg[h->value[left]] < deg[h->value[largest]]){
        largest = left;
    }

    if(right < h->index && deg[h->value[right]] < deg[h->value[largest]]){
        largest = right;
    }

    if(largest != i){
        exchange(h->value,largest,i);
        exchange(position,h->value[largest],h->value[i]);
        max_heapfy_degDouble(h,deg,position,largest);
    }
}

unsigned long pop_heap_degDouble(heap* h, double* deg, unsigned long* position){
    unsigned long p = h->value[0];

    if(h->index == 0){
        printf("fail: heap is empty\n");
        exit(EXIT_FAILURE);
    }

    h->value[0]  = h->value[h->index-1];
    position[h->value[h->index-1]] = 0;
    h->index--;
    down_heap_degDouble(h,deg,0,position);

    return p;
}
