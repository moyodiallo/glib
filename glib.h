/**
 * @brief 
 * 
 */

#ifndef _GLIB_H_
#define _GLIB_H_

typedef struct {
	unsigned long x;
	unsigned long y;
} couple;

typedef struct triangle{
	unsigned long p_1;
	unsigned long p_2;
	unsigned long p_3;
}triangle;

typedef struct {
	unsigned long s;
	unsigned long t;
} edge;

typedef struct heap
{
	unsigned long* value;
	unsigned long size;
	unsigned long index;
}heap;


heap* make_heap(unsigned long size);
void free_heap(heap* h);
void push_heap(heap* h, unsigned long* deg, unsigned long node, unsigned long* position);
unsigned long pop_heap(heap* h, unsigned long* deg, unsigned long* position);
void percolate(heap* h, unsigned long* deg, unsigned long* position);

/**
 * @brief 
 * 
 * @param h 
 * @param deg 
 * @param index 
 * @param position the position in the heap
 */
void up_heap(heap *h, unsigned long *deg, unsigned long index, unsigned long *position);
void down_heap(heap *h, unsigned long *deg, unsigned long index, unsigned long *position);



/**
 * edge list structure:
 * node id start in 1
*/
typedef struct edgelist{
	unsigned long n;        /*number of nodes (properly the maximum id)*/
	unsigned long e;        /*number of edges*/
	edge *edges;            /*list of edges*/
    char directed;        /*1 if directed else 1*/
} edgelist;

edgelist*  make_edgelist_file(char* input, int n_of_nodes, int n_of_edges, char directed);

/**
 * edge list structure:
 * node id begin start in 1
*/
typedef struct adjlist{
    unsigned long n;        /*number of nodes (properly the maximum id)*/
	unsigned long e;        /*number of edges*/
    char directed;        /*1 if directed else 0*/
    unsigned long *cd;      /*cumulative degree cd[0]=0 length=n+1*/
	unsigned long *adj;     /*concatenated lists of neighbors of all nodes*/
} adjlist;

adjlist*   make_adjlist_edges(edgelist*);

/*
	edge list structure:
	This structure is not suitable to manipulate a graph
*/
typedef struct adjmatrix{
    unsigned long n;        /*number of nodes (properly the maximum id)*/
	unsigned long e;        /*number of edges*/
    char directed;        /*1 if directed else 0*/
	char* mat;              /*adjacency matrix*/
} adjmatrix;

adjmatrix* make_adjmatrix_edges(edgelist*);

/*
	generate a graph with 4 cluster
	each pair of node in same cluster is connected with probability p
	each pair of node in different cluster is connected with probability q
	the graph is printed
	the probability is between [0-1]
*/
void generate_clusters(unsigned long n_of_nodes, unsigned long n_of_cluster, double p, double q);

/*
	return number of neighbor
*/
unsigned long n_of_neighbor(adjlist*, unsigned long n);

/*
	for shuffling a vector
*/
void shuffle_random(unsigned long* vector, unsigned long size);

/*
	free the structures
*/
void free_edgelist(edgelist*);
void free_adjlist(adjlist*);
void free_adjmatrix(adjmatrix*);

/*
	couple 
		x -> n_of_nodes
		y -> n_of_edges
*/
couple n_of_graph(char*);

/*
	label propagation algorithme
	label 0 is not assigned
	n times 
*/
unsigned long* label_propagation(adjlist*, int n,int* stop);

/*
	printing for testing little graphs
*/
void print_adjlist(adjlist*);
void print_edgelsit(edgelist*);
void print_n_of_graph(char*);

/**
 * 	random int (min,max)
 */
int random_int(int min, int max);


/**
 * direct the edges by minimum deg
 */
void direct_by_deg(edgelist*);


/**
 * A fifo
 * When pop return 0 if empty
 * if f_full = 1 so the tab have been full at least once
 */
typedef struct fifo{
	int i;
	int j;
	unsigned long size;
	unsigned long* value;
}fifo;

fifo* make_fifo(unsigned long size);
unsigned long pop_fifo(fifo*);
void push_fifo(fifo*, unsigned long val);
void free_fifo(fifo*);
int is_full_fifo(fifo*);
int is_empty_fifo(fifo*);

/**
 * @brief Compute triangle of adjacency list
 * status :
 * 		1 -> print
 * 		0 -> no print
 * 	return the number of triangles
 */
unsigned long compute_triangle(adjlist*, unsigned long* belongs, int print);

/** 
 * @brief bfs breath-first-search
 * \fn
 * \param adjlist
 * \param s source of the walk
 * \param mark mark when the is reached
 * \param c the color for this walk
 * 
 * \return a couple (size,the lower bound)
 */
unsigned long bfs(adjlist*, unsigned long s, unsigned long* mark, unsigned long c, int print);

/**
 * @brief compute connected component
 * 
 */
void connected(adjlist*, int print);

/**
 * @brief compute the diameter of the good bound
 * 
 */
unsigned long diameter(adjlist*, unsigned long s);


/**
 * @brief 
 * 
 * @param alpha 
 * @param theta 
 * @param nodes 
 * @return double* 
 */
double* page_rank(edgelist*, double alpha, unsigned theta, int trace);

/**
 * @brief 
 * 
 * @param e_list 
 * @param T 
 * @param P 
 * @return double* 
 */
double* prod_mat_vect3(edgelist* e_list, double* T, double* P);

/**
 * @brief 
 * 
 * @param P 
 * @param nodes 
 * @param size 
 * @param P_1 
 */
void normalize2(double* P, unsigned long nodes, unsigned long size, double P_1);

/**
 * @brief 
 * 
 * @param P 
 * @param P_N 
 * @param n 
 * @return int 
 */
int equals_P(double* P, double* P_N, unsigned long n);

/**
 * @brief 
 * 
 * @param a_list 
 * @param n_deg 
 * @param core_node 
 * @param num_node 
 * @return unsigned long 
 */
unsigned long kcore(adjlist *a_list , unsigned long *n_deg, unsigned long *core_node, unsigned long *num_node);


/**
 * @brief compute communaty by triangle
 * 
 * @param adjlist adjacency array
 * @return unsigned* the node with the communauty the belongs to
 */
unsigned* communauty_triangle(adjlist* a_list);

/**
 * @brief 
 * 
 * @param a_list 
 * @param core_node 
 * @param pref_node 
 */
void kcore_density(adjlist *a_list, unsigned long *core_node, unsigned long *pref_node);

/**
 * @brief 
 * 
 * @param e_list 
 * @param times 
 * @return unsigned* density_score 
 */
double* density_score(edgelist *e_list, int times);

#endif
