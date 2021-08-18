# -*- coding: utf-8 -*-
"""
Created on Sun Jul 12 10:26:45 2020

@author: Grant
"""

# Weighted Directed Graph Implementation in Python


# data structure to store graph edges
class Edge:
	def __init__(self, src, dest, weight):
		self.src = src
		self.dest = dest
		self.weight = weight


# data structure for adjacency list node
class Node:
	def __init__(self, value, weight):
		self.value = value
		self.weight = weight


# class to represent a graph object
class Graph:
	# Constructor to construct graph
	def __init__(self, edges):

		# A list of lists to represent adjacency list
		self.adj = [None] * len(edges)

		# allocate memory for adjacency list
		for i in range(len(edges)):
			self.adj[i] = []

		# add edges to the undirected graph
		for e in edges:
			# allocate node in adjacency List from src to dest
			node = Node(e.dest, e.weight)
			self.adj[e.src].append(node)


# print adjacency list representation of graph
def printGraph(graph):
	for src in range(len(graph.adj)):
		# print current vertex and all its neighboring vertices
		for edge in graph.adj[src]:
			print(f"({src} -> {edge.value}, {edge.weight}) ", end='')
		print()

edges = [Edge(1, 2, 6), Edge(2, 3, 7), Edge(2, 4, 3), Edge(3, 1, 5),
		Edge(3, 2, 4), Edge(4, 3, 10)]

graph = Graph(edges)

#printGraph(graph)

def FloydWarshall(graph):
    n = 5

    A = [[ [None for col in range(n)] for col in range(n)] for row in range(n)]

    #print(A)

    for i in range(1, n):
        for j in range(1, n):
            if i == j:
                A[i][j][0] = 0
                continue
        
            b = 0
            for src in range(len(graph.adj)):
                for edge in graph.adj[src]:
                    if src == i and edge.value == j:
                        A[i][j][0] = edge.weight
                        b = 1
                        break
            
                if b == 1:
                    break
            if b == 1:
                continue
        
            A[i][j][0] = 100

    #print(A)

    B = [ [None for col in range(n)] for col in range(n)]

    for k in range(1, n):
        for i in range(1, n):
            for j in range(1, n):
                case_1 = A[i][j][k - 1]
                case_2 = A[i][k][k - 1] + A[k][j][k - 1]
            
                min_value = min(case_1, case_2)
            
                A[i][j][k] = min_value
            
                if (min_value == case_2):
                    if k != j and k != i:
                        B[i][j] = k

    for i in range(1, n):
        if (A[i][i][n - 1] < 0):
            print("Negative Cycle Detected")

    print(A)
    print(B)

FloydWarshall(graph)