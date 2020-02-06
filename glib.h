#ifndef _GLIB_H_
#define _GLIB_H_

typedef struct {
	unsigned long s;
	unsigned long t;
} edge;

/*edge list structure:*/
typedef struct edgelist{
	unsigned long n;        /*number of nodes*/
	unsigned long e;        /*number of edges*/
	edge *edges;            /*list of edges*/
    char directed;        /*1 if directed else 1*/
} edgelist;

/*edge list structure:*/
typedef struct adjlist{
    unsigned long n;        /*number of nodes*/
	unsigned long e;        /*number of edges*/
    char undirected;        /*1 if directed else 0*/
    unsigned long *cd;      /*cumulative degree cd[0]=0 length=n+1*/
	unsigned long *adj;     /*concatenated lists of neighbors of all nodes*/
} adjlist;

/*edge list structure:*/
typedef struct adjmatrix{
    unsigned long n;        /*number of nodes*/
	unsigned long e;        /*number of edges*/
    char undirected;        /*1 if directed else 0*/
	char* mat;              /*adjacency matrix*/
} adjmatrix;

/*build from file*/
edgelist*  make_edgelist_file(char* input, int n_of_nodes, int n_of_edges, char directed);

/*build from edges list*/
adjlist*   make_adjlist_edges(edgelist*);
adjmatrix* make_adjmatrix_edges(edgelist*);


void free_edgelist(edgelist*);
void free_adjlist(adjlist*);
void free_adjmatrix(adjmatrix*);

#endif
