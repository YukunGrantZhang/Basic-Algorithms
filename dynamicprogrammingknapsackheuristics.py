# -*- coding: utf-8 -*-
"""
Created on Wed Jul 15 10:17:05 2020

@author: Grant
"""

def round_down(num, divisor):
    return num - (num%divisor)

items = [[12, 1], [14, 3], [13, 3], [10, 2]]
w = 5

values = []
for i in range(0, len(items)):
    values.append(items[i][0])

epsilon = 0.8

m = epsilon * (max(values)) / len(items)

print(m)

for e in range(0, len(items)):
    items[e][0] = round_down(items[e][0], m)
    items[e][0] = int(items[e][0] / m)

print(items)

v_list = []
for i in range(0, len(items)):
    v_list.append(items[i][0])

print(v_list)

v_max = max(v_list)
n = len(items)

n_max = n * v_max

A = []

for a in range(0, n + 1):
    A.append([])

print(A)

for x in range(0, n * v_max + 1):
    if x == 0:
        A[0].append(0)
    else:
        A[0].append(100)

print(A)

for i in range(1, n + 1):
    for x in range(0, n * v_max + 1):
        case_1 = A[i - 1][x]
        if items[i - 1][0] >= x:
            case_2 = items[i - 1][1]
        else:
            case_2 = A[i - 1][x - items[i - 1][0]] + items[i - 1][1]
        
        A[i].append(min(case_1, case_2))

print(A)

largest_x = 0
x = 0
while (A[n][x] <= w):
    largest_x = A[n][x]
    x += 1
    
print(largest_x)
