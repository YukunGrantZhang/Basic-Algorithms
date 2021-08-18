# -*- coding: utf-8 -*-
"""
Created on Wed Jul 15 15:19:49 2020

@author: Grant
"""

class Edge:
	def __init__(self, src, dest, weight):
		self.src = src
		self.dest = dest
		self.weight = weight

class Node:
	def __init__(self, value, weight):
		self.value = value
		self.weight = weight
        
class Graph:
    def __init__(self, edges, size):
        self.adj = [[] for _ in range(size)]
        
        for current in edges:
            self.adj[current.src].append(Node(current.dest, current.weight))
            self.adj[current.dest].append(Node(current.src, current.weight))
    
def printGraph(graph):
	for src in range(len(graph.adj)):
		# print current vertex and all its neighboring vertices
		for edge in graph.adj[src]:
			print(f"({src} -> {edge.value}, {edge.weight}) ", end="")
		print()

def maximumcut(graph, n, starting_vertex):
    A = []
    B = []
    
    for i in range(0, n):
        if i == starting_vertex:
            B.append(i)
        else:
            A.append(i)
    
    chosen_vertex = 100
    chosen_Cv = 100
    chosen_Dv = 100
    
    for vertex in A:
        Cv = 0
        Dv = 0
        for node in graph.adj[vertex]:
            if node.value in B:
                Cv += node.weight
            
            if node.value in A:
                Dv += node.weight
        
        if Dv > Cv:
            chosen_vertex = vertex
            chosen_Cv = Cv
            chosen_Dv = Dv
            break
    
    if chosen_vertex != 100:
        B.append(chosen_vertex)
        A.remove(chosen_vertex)
    else:
        max_cut = 0
        for v in A:
            for node in graph.adj[v]:
                if node.value in B:
                    max_cut += node.weight
    
        return max_cut
        
    while (chosen_Dv > chosen_Cv):
        previous_vertex = chosen_vertex
        for vertex in A:
            Cv = 0
            Dv = 0
            for node in graph.adj[vertex]:
                if node.value in B:
                    Cv += node.weight
            
                if node.value in A:
                    Dv += node.weight
            
            chosen_Cv = Cv
            chosen_Dv = Dv
            
            if chosen_Dv > chosen_Cv:
                chosen_vertex = vertex
                break
        
        if chosen_vertex != previous_vertex:
            B.append(chosen_vertex)
            A.remove(chosen_vertex)
    
    max_cut = 0
    for v in A:
        for node in graph.adj[v]:
            if node.value in B:
                max_cut += node.weight
    
    return max_cut

edges = [Edge(1, 0, 1), Edge(1, 2, 3), Edge(1, 3, 3), 
         Edge(1, 4, 5), Edge(1, 5, 6)]

graph = Graph(edges, 6)

printGraph(graph)

original_graph = Graph(edges, 6)

max_list = []
for a in range(0, len(graph.adj)):
    graph = original_graph
    max_list.append(maximumcut(graph, 6, a))

print(max(max_list))