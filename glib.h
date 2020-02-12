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
void generate4clusters(unsigned long n_of_nodes, double p, double q);

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
unsigned long* label_propagation(adjlist*, int n);

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
unsigned long compute_triangle(adjlist*, int print);

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
unsigned long diameter(adjlist*, unsigned long s, int print);

/**
 * @brief page Rank
 * 
 */
unsigned long* page_rank(edgelist*,unsigned long size,int print);

#endif
