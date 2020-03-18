#include <stdio.h>
#include <stdlib.h>

#include "glib.h"

int main(int argc, char** argv){
    if (argc != 7){
        printf("fail: cmd <file> <n_of_node> <n_of_edges> <alpha> <it> <p,i,o,n,t>");
        exit(EXIT_FAILURE);
    }

    unsigned long i,j,node = 0;
    unsigned long* nodes;
    double* rank,max;
    char* file  = argv[1]; 

    unsigned long n_of_node = atoi(argv[2]);
    unsigned long n_of_edge = atoi(argv[3]);
    
    double alpha = atof(argv[4]);
    unsigned it  = atoi(argv[5]);

    edgelist* e_list = make_edgelist_file(file,n_of_node,n_of_edge,1);
    

    if(argv[6][0] == 't')
        rank = page_rank(e_list,alpha,it,1);
    else
        rank = page_rank(e_list,alpha,it,0);


    if(argv[6][0] == 'p'){
        for (i = 1; i < e_list->n; i++)
        {
            if(rank[i] != 0.0){
                printf("%lu %f\n",i,rank[i]*100);
            }
        }
    }

    if(argv[6][0] == 'n' || argv[6][0] == 't'){
        for ( j = 0; j < 20; j++)
        {
            max = 0;

            for (i = 1; i < e_list->n+1; i++)
            {
                if(max < rank[i]){
                    node = i;
                    max  = rank[i]; 
                }
            }
            
            printf("%lu %f\n",node,rank[node]*100);
            rank[node] = 0;
        }
    }


    nodes = calloc(e_list->n+1,sizeof(unsigned long));
    if(argv[6][0] == 'i'){
        for (i = 0; i < e_list->e; i++)
        {
            nodes[ e_list->edges[i].t]++;
        }

        for (i = 1; i < e_list->n; i++)
        {
            if(rank[i] != 0.0){
                printf("%lu %lf %lu\n",i,rank[i]*100,nodes[i]);
            }
        }
        
    }

    if(argv[6][0] == 'o'){
        for (i = 0; i < e_list->e; i++)
        {
            nodes[ e_list->edges[i].s]++;
        }

       for (i = 1; i < e_list->n; i++)
        {
            if(rank[i] != 0.0){
                printf("%lu %lf %lu\n",i,rank[i]*100,nodes[i]);
            }
        }
    }

    free(nodes);
    free_edgelist(e_list);
    free(rank);
    
}
