# -*- coding: utf-8 -*-
"""
Created on Tue Jul 14 13:35:15 2020

@author: Grant
"""

class Edge:
	def __init__(self, src, dest):
		self.src = src
		self.dest = dest
        
class Graph:
    def __init__(self, edges, size):
        self.adj = [[] for _ in range(size)]
        
        for current in edges:
            self.adj[current.src].append(current.dest)
            self.adj[current.dest].append(current.src)

minimum = 100

def mincover(graph, edges, n, count):
    global minimum
    
    selected_vertex = 100
    for src in range(len(graph.adj)):
        if graph.adj[src] != []:
            selected_vertex = src
            break
    
    if selected_vertex == 100:
        if count < minimum:
            minimum = count
        return
    
    original_graph = Graph(edges, n)
    for x in range(len(graph.adj)):
        original_graph.adj[x] = graph.adj[x]
    original_count = count
    opposite_vertex = graph.adj[selected_vertex][0]

    graph.adj[selected_vertex] = []
    for a in range(len(graph.adj)):
        for b in graph.adj[a]:
            if b == selected_vertex:
                graph.adj[a].remove(b)    
    count += 1    
    mincover(graph, edges, n, count)
    
    original_graph.adj[opposite_vertex] = []
    for a in range(len(original_graph.adj)):
        for b in original_graph.adj[a]:
            if b == opposite_vertex:
                original_graph.adj[a].remove(b)
    original_count += 1
    mincover(original_graph, edges, n, original_count)


edges = [Edge(0, 1), Edge(0, 2), Edge(0, 3), Edge(0, 4),
			 Edge(0, 5)]

graph = Graph(edges, 6)

mincover(graph, edges, 6, 0)

print(minimum)