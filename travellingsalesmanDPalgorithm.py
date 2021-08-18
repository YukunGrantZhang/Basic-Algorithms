# -*- coding: utf-8 -*-
"""
Created on Tue Jul 14 15:00:38 2020

@author: Grant
"""

import itertools

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

edges = [Edge(1, 2, 2), Edge(1, 3, 1), Edge(1, 4, 3), 
         Edge(2, 3, 4), Edge(2, 4, 5),
		 Edge(3, 4, 6)]

graph = Graph(edges, 5)

#printGraph(graph)

A = []

n = 4

for i in range(0, n + 1):
    A.append([None] * (n + 1))

#print(A)

for a in range(1, n + 1):
    if a == 1:
        A[a][1] = 0
    else:
        A[a][1] = 100

#print(A)

a = [1,2,3,4]
size_combinations = [None]
for i in range(1,len(a)+1):
   size_combinations.append(list(itertools.combinations(a,i)))
#print(size_combinations)

new_combinations = [None]
for x in range(1, len(size_combinations)):
    temp = []
    for y in range(len(size_combinations[x])):
        temp_tuple = size_combinations[x][y]
        if 1 in temp_tuple:
            #print(temp_tuple)
            temp.append(temp_tuple)
    new_combinations.append(temp)
            
#print(size_combinations)
#print(new_combinations)

for m in range(2, n + 1):
    for s in new_combinations[m]:
        for j in range(0, len(s)):
            if s[j] == 1:
                continue
            """
            c = 100
            
            if m == 2:
                for u in graph.adj[1]:
                    if u.value == s[j]:
                        c = u.weight
                        A[m][s[j]] = A[m - 1][1] + c
                        break
            
            if c != 100:
                continue
            """
            minimum_list = []
            
            for k in range(0, len(s)):
                #if k == j or s[k] == 1:
                if k == j:
                    continue
                
                c = 100
                for u in graph.adj[s[k]]:
                    if u.value == s[j]:
                        c = u.weight
                        break
                
                #print(m - 1)
                #print(s[k])
                #print(A[m - 1][s[k]])
                #print(c)
                #print()
                
                #if A[m - 1][s[k]] == None:
                #    continue
                
                temp = A[m - 1][s[k]] + c
                
                minimum_list.append(temp)
            
            A[m][s[j]] = min(minimum_list)
            #if minimum_list != []:
            #    A[m][s[j]] = min(minimum_list)
            #else:
            #    A[m][s[j]] = c
            #print(A) 



#print(A)

answer = A[4]

min_distances = []

for a in range(2, len(answer)):
    for u in graph.adj[1]:
        if u.value == a:
            c = u.weight
            break
    
    temp = answer[a] + c
    
    min_distances.append(temp)

minimum = min(min_distances)
print(minimum)
    
    
            
            
    

