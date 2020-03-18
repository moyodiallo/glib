#include <stdio.h>
#include <stdlib.h>

#include "glib.h"

int main(int argc, char** argv){
    if (argc != 5){
        printf("fail: cmd <file> <n_of_node> <n_of_edges> <p or n>");
        exit(EXIT_FAILURE);
    }

    int print;
    if(argv[4][0] == 'p')
        print = 1;
    else if(argv[4][0] == 'n')
        print = 0;
    else if(argv[4][0] == 's')
        print = 2;
    else
    {
        printf("fail: cmd <file> <n_of_node> <n_of_edges> <p or n>");
        exit(EXIT_FAILURE);
    } 

    
    char* file  = argv[1]; 
    unsigned long n_of_node = atoi(argv[2]);
    unsigned long n_of_edge = atoi(argv[3]);
    unsigned long count,i,v_edge,total;
    double coeff_node;

    double ratio = 0.0;
    double coeff = 0.0;

    unsigned long* belongs = calloc(n_of_node+1,sizeof(unsigned long));

    /*the edge list have to be directed*/
    edgelist* e_list = make_edgelist_file(file,n_of_node,n_of_edge,1);

    adjlist*  a_list = make_adjlist_edges(e_list); 
    free(e_list);

    count = compute_triangle(a_list,belongs,print);
    free(a_list);
    
    e_list = make_edgelist_file(file,n_of_node,n_of_edge,0);
    unsigned long* deg = calloc(n_of_node+1,sizeof(unsigned long));
    for (i = 0; i < n_of_edge; i++)
    {
        deg[e_list->edges[i].s]++;
        deg[e_list->edges[i].t]++;
    }

    v_edge = 0;
    total  = 0;
    for (i = 1; i < n_of_node+1; i++)
    {
        v_edge += ((deg[i]*(deg[i]-1))/2);
        if(deg[i] > 1){
            coeff_node = (((double)(belongs[i])) / ((deg[i]*(deg[i]-1))/2)); 
            coeff     += coeff_node;
            total++;

            if(print == 2){
                printf("%lu %f\n",i,coeff_node);
            }
        }
    }

    ratio = ((double)(3*count))/(v_edge);
    coeff = coeff/(total);

    free(deg);
    free(belongs);

    if(argv[4][0] == 'n'){
        printf("triangles              = %lu\n",count);
        printf("transitivity ratio     = %f\n" ,ratio);
        printf("clustering coefficient = %f\n" ,coeff);
    }
}
