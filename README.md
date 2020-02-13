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
p = pint all component important for debuging
s = print the size of each connected component
m = print the size of big connected component and a node of this component

./connected <file> <n_of_node> <n_of_edge> <p or n>
```

## Compute the good bound diameter of the big component
This compute the good bound diameter of a graph, like known a graph can have many 
connected components
```
p = print the diameter of each connected component
n = print the diameter of good lower bound

./diameter <file> <n_of_node> <n_of_edge> <node_amount> <p or n>
```

## Compute the triangles
To compute triangles, you have follow execute some commands before(Preparing the graph)

### Preparing the graph
```

```

### computing triangle
```
./triangle <file>
```

## Compute communauties

To validate a communauties dectection algorithm, you have generate some clusters that you know
for testing your algorithm.

### Clusters generating

### Using label propagation

### Using 3-clique

### Page Rank


## Benchmarks