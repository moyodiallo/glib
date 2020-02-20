# Graphs Handling

The graph format must be like, no loop and your node must begin 
by 1 and never mind for espace or tab to separate the nodes of a edges:
```
1 2
2 3
3 4
4 5
```

![Graph of ./data/test.txt](.images/test.png)



## Compute number of nodes and edges 
Before to manipulate a graph you have know some proprieties
```
./n_of_node <file>
```

``` example:
./n_of_node data/test.txt

Output:
n_of_node :
n_of_edge :
```

## Compute connected components
The algorithm used is [BFS!](https://en.wikipedia.org/wiki/Breadth-first_search)
```
print_args:
p = pint all component important for debuging
s = print the size of each connected component
m = print the size of big connected component and a node of this component and the total components

./connected <file> <n_of_node> <n_of_edge> <print_args>
```

## Compute the good bound diameter of the big component
Compute the good lower bound diameter of a graph, like known a graph can have many 
connected components
```
p = print the diameter of each connected component
n = print the diameter of good lower bound

./diameter <file> <n_of_node> <n_of_edge> <node_amount> <p or n>
```

## Compute the triangles
To compute triangles, you have follow execute some commands before(Preparing the graph)

### Preparing the graph
For the results to be true, you have to prepare the file.
```
./direct_by_deg <file_orignal> <n_of_node> <n_of_edges> > <file_directed>
sort -n k2 <file_directed> > <file_directed_sorted>
```

### computing triangle
After file prepared, you can compute triangles.
```
p = print all triangles
n = print the number of triangles

./triangle <file_directed_sorted> <n_of_node> <n_of_edge> <p or n>
```

## Compute communauties

To validate a communauties dectection algorithm, you have generate some clusters that you know
for testing your algorithm.

### Clusters generating

Generate clusters and for each link (u,v), node u and node v in the same cluster with
have a link with probability p and not with the probability q. Probability ([0.0-1.0])

+ n_of_node    : min 100 nodes
+ n_of_cluster : max 10 clusters

```
./cluster <n_of_node> <n_of_group> <p> <q>

Example:
./cluster 400 4 0.6 0.005 > clusters0.txt
```


### Using label propagation

### Using 3-clique

### Page Rank
Page Rank implemented

p = print (node,page_rank value)
i = print (page_rank,deg_in of page) 
o = print (page_rank,deg_out of page)
n = print the 20 ranked page (page id,page_rank)
t = print iterations

```
./page_rank <file> <n_of_edge> <n_of_edge> <alpha> <theta> <p,i,o,or n>
```

## Benchmarks