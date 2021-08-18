 # -*- coding: utf-8 -*-
"""
Created on Thu Jul  9 15:36:20 2020

@author: Grant
"""

W = 6

P = [1, 2, 3, 4]

v = [3, 2, 4, 4]

w = [4, 3, 2, 3]

A = []

for i in range(0, len(v) + 1):
    A.append([])

for j in range(0, W + 1):
    A[0].append(0)

n = len(v) + 1
W_n = W + 1

for a in range(1, n):
    for b in range(0, W_n):
        if b - w[a - 1] >= 0:
            case_1 = A[a - 1][b]
            case_2 = A[a - 1][b - w[a - 1]] + v[a - 1]
            max_value = max(case_1, case_2)
        else:
            max_value = A[a - 1][b]
        
        A[a].append(max_value)

S = []

m = n - 1
weight_index = W_n - 1

while m >= 1:
    if weight_index - w[m - 1] < 0:
        m -= 1
        continue
    
    if A[m - 1][weight_index] >= A[m - 1][weight_index - w[m - 1]] + v[m - 1]:
        m -= 1
    else:
        S.append(P[m - 1])
        weight_index -= w[m - 1]
        m -= 1

print(S)
    

