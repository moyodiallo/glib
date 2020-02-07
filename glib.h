#ifndef _GLIB_H_
#define _GLIB_H_

typedef struct {
	unsigned long x;
	unsigned long y;
} couple;

typedef struct {
	unsigned long s;
	unsigned long t;
} edge;

/*edge list structure:*/
typedef struct edgelist{
	unsigned long n;        /*number of nodes (properly the maximum id)*/
	unsigned long e;        /*number of edges*/
	edge *edges;            /*list of edges*/
    char directed;        /*1 if directed else 1*/
} edgelist;

/*edge list structure:*/
typedef struct adjlist{
    unsigned long n;        /*number of nodes (properly the maximum id)*/
	unsigned long e;        /*number of edges*/
    char directed;        /*1 if directed else 0*/
    unsigned long *cd;      /*cumulative degree cd[0]=0 length=n+1*/
	unsigned long *adj;     /*concatenated lists of neighbors of all nodes*/
} adjlist;

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

/*build from file*/
edgelist*  make_edgelist_file(char* input, int n_of_nodes, int n_of_edges, char directed);

/*build from edges list*/
adjlist*   make_adjlist_edges(edgelist*);
adjmatrix* make_adjmatrix_edges(edgelist*);

/*
	build from edges list by sorting neighbors nodes
*/
adjlist*   make_adjlist_edges_sort(edgelist*);

/*
	generate a graph with 4 cluster
	each pair of node in same cluster is connected with probability p
	each pair of node in different cluster is connected with probability q
	the graph is printed
	the probability is between [0-1]
*/
void generate4clusters(unsigned long n_of_nodes, double p, double q);


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
	
*/

/*
	printing for testing little graphs
*/
void print_adjlist(adjlist*);
void print_edgelsit(edgelist*);
void print_n_of_graph(char*);

#endif
