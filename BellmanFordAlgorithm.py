# -*- coding: utf-8 -*-
"""
Created on Sat Jul 11 09:54:15 2020

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
	def __init__(self, edges):

		self.adj = [None] * len(edges)

		for i in range(len(edges)):
			self.adj[i] = []

		for e in edges:
			node = Node(e.dest, e.weight)
			self.adj[e.src].append(node)

edges = [Edge(0, 1, 2), Edge(0, 2, 4), Edge(1, 3, 2),
		Edge(1, 2, 1), Edge(2, 4, 4), Edge(3, 4, 2)]

graph = Graph(edges)

def BellmanFord(graph, start):
    A = []

    n = 5

    for i in range(0, n + 1):
        A.append([])

    Initial_row = []

    starting_vertex = start

    for i in range(0, n):
        if i == starting_vertex:
            Initial_row.append(0)
        else:
            Initial_row.append(100)

    A[0] = Initial_row
    
    B = []

    n = 5

    for i in range(0, n + 1):
        B.append([])
        
    for i in range(0, n):
        B[0].append(None)

    for i in range(1, n + 1):
        for v in range(0, n):
        
            case_1 = A[i - 1][v]
        
            w = []
            e = []
        
            for src in range(len(graph.adj)):
                for edge in graph.adj[src]:
                    if edge.value == v:
                        w.append(src)
                        e.append(edge.weight)
        
            total = []
            for b in range(len(w)):
                total.append(A[i - 1][w[b]] + e[b])
        
            if total != []:
                case_2 = min(total)
                A[i].append(min(case_1, case_2))
                
                chosen_case = min(case_1, case_2)
                
                if chosen_case == case_1:
                    B[i].append(B[i - 1][v])
                else:
                    chosen_index = total.index(min(total))
                    vertex = w[chosen_index]
                    B[i].append(vertex)
            else:
                A[i].append(case_1)
                B[i].append(B[i - 1][v])
        
        if i == n:
            if A[n - 1] != A[n]:
                print("Negative Cycle Detected!")
                return
        
    nodes = [*range(0, n)]
    min_distances = A[len(A) - 1]
    print(nodes)
    print(min_distances)
    
    print(B[len(B) - 1])

BellmanFord(graph, 0)