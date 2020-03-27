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
from matplotlib.cm import get_cmap

filepath_links      = sys.argv[1]
filepath_node_color = sys.argv[2]

index_p = 0
palette = get_cmap('tab10').colors


color = {}
nodes = {}
edges = []


print("loading colors")
with open(filepath_node_color) as fp:
    line = fp.readline()
    while line:
        points = line.split(' ')
        if int(points[1]) in color.keys():
            nodes[color[int(points[1])]].append(int(points[0]))
        else:
            color[ int(points[1]) ] = palette[index_p]
            index_p = index_p + 1
            nodes[color[int(points[1])]] = [int(points[0])]
        line = fp.readline()

print("loading colors finished")

print("loading nodes")
with open(filepath_links) as fp:  
   line = fp.readline()
   while line:
       points = line.split(' ')
       edges.append((int(points[0]),int(points[1])))
       line = fp.readline()

print("loading node finished")

G = nx.Graph()
G.add_edges_from(edges)
pos = nx.spring_layout(G)

options = {
    "node_size": 20,
    "line_color": "grey",
    "linewidths": 0,
    "width": 0.1,
}

for col in nodes.keys():
    nx.draw_networkx_nodes(G, pos, nodelist=nodes[col], node_color=col,**options)

nx.draw_networkx_edges(G,pos,width=0.5)


plt.show()