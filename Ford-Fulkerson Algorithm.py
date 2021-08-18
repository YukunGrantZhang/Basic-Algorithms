# -*- coding: utf-8 -*-
"""
Created on Thu Jul 16 17:13:58 2020

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
        self.flows = 0

class Graph:
    def __init__(self, edges, size):
        self.adj = [[] for _ in range(size)]
        
        for current in edges:
            self.adj[current.src].append(Node(current.dest, current.weight))
    
def printGraph(graph):
	for src in range(len(graph.adj)):
		# print current vertex and all its neighboring vertices
		for edge in graph.adj[src]:
			print(f"({src} -> {edge.value}, {edge.weight}) ", end="")
		print()

temp_bottleneck = 100
last_vertex = 5
path_nodes = []

def DepthFirstSearch(graph, vertex):
    global path_nodes
    global temp_bottleneck
    global last_vertex
    
    path_nodes.append(vertex)
    
    if vertex == 5:
        last_vertex = 5
        return
    
    for edge in graph.adj[vertex]:           
        if edge.flows < edge.weight:
            addition = edge.weight - edge.flows
            if temp_bottleneck > addition:
                temp_bottleneck = addition
                
            DepthFirstSearch(graph, edge.value)
            break
        
        i = 0
        for x in range(len(graph.adj)):
            i = 0
            for y in graph.adj[x]:
                if y.value == vertex and y.flows == y.weight and x not in path_nodes:
                    DepthFirstSearch(graph, x)
                    i = 1
                    break
            if i == 1:
                break
        if i == 1:
            break

def updateflows(graph):
    global temp_bottlenecks
    global path_nodes
    
    for i in range(len(path_nodes) - 1):
        vertex = path_nodes[i]
        dest = path_nodes[i + 1]
        
        n = 0
        
        for y in graph.adj[vertex]:
            if y.value == dest and y.flows < y.weight:
                y.flows += temp_bottleneck
                n = 1
                break
        
        if n == 1:
            continue
        
        for y in graph.adj[dest]:
            if y.value == vertex and y.flows == y.weight:
                y.flows -= temp_bottleneck
                n = 1
                break
    
    graph.adj[5][0].flows += temp_bottleneck
        
def FordFulkerson(graph, starting_vertex):
    global temp_bottleneck
    global last_vertex
    global path_nodes
    
    last_vertex = 5
    
    while last_vertex == 5:
        path_nodes.clear()
        last_vertex = 100
        DepthFirstSearch(graph, 0)
        if last_vertex == 5:
            updateflows(graph)
        temp_bottleneck = 100

    print(graph.adj[5][0].flows)    

edges = [Edge(0, 1, 9), Edge(0, 2, 10), 
         Edge(1, 2, 2), Edge(1, 3, 4), Edge(1, 4, 8),
         Edge(2, 4, 9),
         Edge(3, 5, 10),
         Edge(4, 3, 6), Edge(4, 5, 10),
         Edge(5, 0, 0)]

graph = Graph(edges, 6)

printGraph(graph)

FordFulkerson(graph, 0)