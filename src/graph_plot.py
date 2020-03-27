#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
Created on Mon Apr  8 21:48:59 2019

@author: alpha
"""


import matplotlib.pyplot as plt
import networkx as nx
import numpy
import sys


filepath = sys.argv[1]
edges = []

with open(filepath) as fp:  
   line = fp.readline()
   while line:
       st = line.split(' ')
       edges.append((int(st[0]),int(st[1])))
       line = fp.readline()

G = nx.Graph()

options = {
    "node_size": 20,
    "line_color": "grey",
    "linewidths": 1,
    "width": 0.1,
}

G.add_edges_from(edges)
#G.add_nodes_from([(10,{'color':'red'})])
#G.add_node(2,node_color='red')
#G.add_edges_from([(1, 2, {'color': 'blue'}), (2, 3, {'weight': 8})])

nx.draw(G,**options)
plt.show()